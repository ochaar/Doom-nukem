/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ennemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 13:33:43 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 01:12:28 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_intersect	init_x1_x2(t_map *m, t_intersect i, int x)
{
	i.x1 = m->ennemy[x].coor.x;
	i.y1 = m->ennemy[x].coor.y;
	i.x2 = m->ennemy[x].coor.x + m->ennemy[x].move_speed.x;
	i.y2 = m->ennemy[x].coor.y + m->ennemy[x].move_speed.y;
	return (i);
}

t_intersect	init_x3_x4(t_map *m, t_intersect i, int x, int s)
{
	i.x3 = m->sector[m->ennemy[x].sector].dot[s].x;
	i.y3 = m->sector[m->ennemy[x].sector].dot[s].y;
	i.x4 = m->sector[m->ennemy[x].sector].dot[s + 1].x;
	i.y4 = m->sector[m->ennemy[x].sector].dot[s + 1].y;
	return (i);
}

void		move_ennemy(double dx, double dy, t_map *m, int x)
{
	int			s;
	t_intersect	i;
	t_coor		coor;
	t_dot		p;

	i.x1 = 0;
	i = init_x1_x2(m, i, x);
	s = 0;
	while (s < m->sector[m->ennemy[x].sector].wall_count)
	{
		i = init_x3_x4(m, i, x, s);
		p.x = i.x3;
		p.y = i.y3;
		coor.x = i.x2;
		coor.y = i.y2;
		if (m->sector[m->ennemy[x].sector].network[s] >= 0 && intersectbox(i)
		&& pointside(coor, p, i.x4, i.y4) <= 0)
		{
			m->ennemy[x].sector = m->sector[m->ennemy[x].sector].network[s];
			break ;
		}
		s++;
	}
	m->ennemy[x].coor.x = m->ennemy[x].coor.x + dx;
	m->ennemy[x].coor.y = m->ennemy[x].coor.y + dy;
}

void		is_moving_ennemy(t_map *m, int x)
{
	int			s;
	t_intersect	i;
	t_coor		coor;
	t_dot		p;

	s = 0;
	i.x1 = 0;
	i = init_x1_x2(m, i, x);
	coor.x = i.x2;
	coor.y = i.y2;
	p.x = i.x3;
	p.y = i.y3;
	i.dx = m->ennemy[x].move_speed.x;
	i.dy = m->ennemy[x].move_speed.y;
	while (s < m->sector[m->ennemy[x].sector].wall_count)
	{
		i = init_x3_x4(m, i, x, s);
		if (intersectbox(i) && pointside(coor, p, i.x4, i.y4) <= 0)
			walk_up_stairs(m, i, x, s);
		s++;
	}
	move_ennemy(m->ennemy[x].move_speed.x, m->ennemy[x].move_speed.y, m, x);
	m->ennemy[x].fall = 1;
}

void		move_all_ennemy(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->ennemy_count)
	{
		if (m->ennemy[i].vis == 1)
		{
			is_fall(m, i);
			is_moving_ennemy(m, i);
		}
		i++;
	}
}
