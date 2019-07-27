/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:03:16 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 01:13:23 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		slow_down(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] || w->inkeys[SDL_SCANCODE_S]
		|| w->inkeys[SDL_SCANCODE_A] || w->inkeys[SDL_SCANCODE_D])
		m->player.press = 1;
	else
		m->player.press = 0;
	if (m->player.press == 1)
		m->player.accel = 0.4;
	else
		m->player.accel = 0.2;
	m->player.move_speed.x = m->player.move_speed.x * (1 - m->player.accel)
		+ m->player.move_speedless.x * m->player.accel;
	m->player.move_speed.y = m->player.move_speed.y * (1 - m->player.accel)
		+ m->player.move_speedless.y * m->player.accel;
	if (m->player.press == 1)
		m->player.moving = 1;
	else
		m->player.moving = 0;
	m->player.move_speedless.x = 0.f;
	m->player.move_speedless.y = 0.f;
}

int			is_on_a_map_dot(t_map *m, int sector)
{
	t_intersect i;
	double		r1;
	double		r2;

	i.mem = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + (m->player.move_speed.x * 5);
	i.y2 = m->player.coor.y + (m->player.move_speed.y * 5);
	while (i.mem < m->sector[sector].wall_count)
	{
		i.x3 = m->sector[sector].dot[i.mem].x;
		i.y3 = m->sector[sector].dot[i.mem].y;
		r1 = (i.x3 - i.x1) * (i.y2 - i.y1);
		r2 = (i.y3 - i.y1) * (i.x2 - i.x1);
		if ((int)r1 == (int)r2)
		{
			if ((i.x3 > vmin(i.x1, i.x2) && i.x3 < vmax(i.x1, i.x2))
				|| (i.y3 > vmin(i.y1, i.y2) && i.y3 < vmax(i.y1, i.y2)))
				return (-1);
		}
		i.mem++;
	}
	return (0);
}

void		move_player(double dx, double dy, t_map *m)
{
	int			s;
	t_intersect	i;
	t_coor		coor;
	t_dot		p;

	s = 0;
	init_x1_x2_mp(m, &i, dx, dy);
	while (s < m->sector[m->player.sector].wall_count)
	{
		init_x3nx4(m, &i, -42, s);
		coor.x = i.x2;
		coor.y = i.y2;
		p = fill_t_dot(i.x3, i.y3);
		if (m->sector[m->player.sector].network[s] >= 0 && intersectbox(i)
		&& pointside(coor, p, i.x4, i.y4) < 0)
		{
			m->player.sector = m->sector[m->player.sector].network[s];
			break ;
		}
		s++;
	}
	m->player.coor.x = m->player.coor.x + dx;
	m->player.coor.y = m->player.coor.y + dy;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		walk_stairs(t_map *m, t_intersect i, int s)
{
	m->player.hole_low = 9e9;
	m->player.hole_high = -9e9;
	if (m->sector[m->player.sector].network[s] >= 0)
		player_hole(m, s);
	if (m->player.hole_high < m->player.coor.z + HEADMARGIN
	|| m->player.hole_low > m->player.coor.z - m->player.height + KNEEH)
	{
		i.xd = m->sector[m->player.sector].dot[s + 1].x
			- m->sector[m->player.sector].dot[s].x;
		i.yd = m->sector[m->player.sector].dot[s + 1].y
			- m->sector[m->player.sector].dot[s].y;
		m->player.move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd)
			/ (i.xd * i.xd + i.yd * i.yd);
		m->player.move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd)
			/ (i.xd * i.xd + i.yd * i.yd);
		m->player.moving = 0;
	}
	if (is_on_a_map_dot(m, m->player.sector) == -1)
	{
		m->player.move_speed.x = 0;
		m->player.move_speed.y = 0;
	}
}

void		is_moving(t_map *m)
{
	int			s;
	t_intersect	i;
	t_coor		coor;
	t_dot		p;

	s = 0;
	init_x1nx2(m, &i, -42);
	coor.x = i.x2;
	coor.y = i.y2;
	i.dx = m->player.move_speed.x;
	i.dy = m->player.move_speed.y;
	while (s < m->sector[m->player.sector].wall_count)
	{
		init_x3nx4(m, &i, -42, s);
		p.x = i.x3;
		p.y = i.y3;
		if (intersectbox(i) && pointside(coor, p, i.x4, i.y4) <= 0)
			walk_stairs(m, i, s);
		s++;
	}
	move_player(m->player.move_speed.x, m->player.move_speed.y, m);
	m->player.fall = 1;
}
