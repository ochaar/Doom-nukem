/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_moving.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 00:54:00 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 01:13:12 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_x1nx2(t_map *m, t_intersect *i, int x)
{
	if (x == -42)
	{
		i->x1 = m->player.coor.x;
		i->y1 = m->player.coor.y;
		i->x2 = m->player.coor.x + m->player.move_speed.x;
		i->y2 = m->player.coor.y + m->player.move_speed.y;
	}
	else
	{
		i->x1 = m->ennemy[x].coor.x;
		i->y1 = m->ennemy[x].coor.y;
		i->x2 = m->ennemy[x].coor.x + m->ennemy[x].move_speed.x;
		i->y2 = m->ennemy[x].coor.y + m->ennemy[x].move_speed.y;
	}
}

void		init_x3nx4(t_map *m, t_intersect *i, int x, int s)
{
	if (x == -42)
	{
		i->x3 = m->sector[m->player.sector].dot[s].x;
		i->y3 = m->sector[m->player.sector].dot[s].y;
		i->x4 = m->sector[m->player.sector].dot[s + 1].x;
		i->y4 = m->sector[m->player.sector].dot[s + 1].y;
	}
	else
	{
		i->x3 = m->sector[m->ennemy[x].sector].dot[s].x;
		i->y3 = m->sector[m->ennemy[x].sector].dot[s].y;
		i->x4 = m->sector[m->ennemy[x].sector].dot[s + 1].x;
		i->y4 = m->sector[m->ennemy[x].sector].dot[s + 1].y;
	}
}

void		init_x1_x2_mp(t_map *m, t_intersect *i, double dx, double dy)
{
	i->x1 = m->player.coor.x;
	i->y1 = m->player.coor.y;
	i->x2 = m->player.coor.x + dx;
	i->y2 = m->player.coor.y + dy;
}

void		player_hole(t_map *m, int s)
{
	m->player.hole_low = vmax(m->sector[m->player.sector].floor,
		m->sector[m->sector[m->player.sector].network[s]].floor);
	m->player.hole_high = vmin(m->sector[m->player.sector].ceiling,
		m->sector[m->sector[m->player.sector].network[s]].ceiling);
}
