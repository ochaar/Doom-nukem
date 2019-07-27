/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fall_and_stair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 19:14:08 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/14 15:01:09 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		last_if(t_map *m, int x)
{
	if (m->ennemy[x].fall == 1)
	{
		m->ennemy[x].coor.z = m->ennemy[x].coor.z
			+ m->ennemy[x].move_speed.z;
		m->ennemy[x].moving = 1;
	}
}

void		is_fall(t_map *m, int x)
{
	double	nxtz;

	m->ennemy[x].height = STAND;
	m->ennemy[x].ground = !m->ennemy[x].fall;
	if (m->ennemy[x].fall == 1)
	{
		m->ennemy[x].move_speed.z = m->ennemy[x].move_speed.z - m->gravity;
		nxtz = m->ennemy[x].coor.z + m->ennemy[x].move_speed.z;
		if (m->ennemy[x].move_speed.z < 0 && nxtz
			< m->sector[m->ennemy[x].sector].floor + m->ennemy[x].height)
		{
			m->ennemy[x].coor.z = m->sector[m->ennemy[x].sector].floor
				+ m->ennemy[x].height;
			m->ennemy[x].move_speed.z = 0;
			m->ennemy[x].fall = 0;
			m->ennemy[x].ground = 1;
		}
		else if (m->ennemy[x].move_speed.z > 0 && nxtz
			> m->sector[m->ennemy[x].sector].ceiling)
		{
			m->ennemy[x].move_speed.z = 0;
			m->ennemy[x].fall = 1;
		}
		last_if(m, x);
	}
}

void		walk_up_stairs(t_map *m, t_intersect i, int x, int s)
{
	m->ennemy[x].hole_low = 9e9;
	m->ennemy[x].hole_high = -9e9;
	if (m->sector[m->ennemy[x].sector].network[s] >= 0)
	{
		m->ennemy[x].hole_low = vmax(m->sector[m->ennemy[x].sector].floor,
			m->sector[m->sector[m->ennemy[x].sector].network[s]].floor);
		m->ennemy[x].hole_high = vmin(m->sector[m->ennemy[x].sector].ceiling,
			m->sector[m->sector[m->ennemy[x].sector].network[s]].ceiling);
	}
	if (m->ennemy[x].hole_high < m->ennemy[x].coor.z + HEADMARGIN
	|| m->ennemy[x].hole_low > m->ennemy[x].coor.z - m->ennemy[x].height + 10)
	{
		i.xd = m->sector[m->ennemy[x].sector].dot[s + 1].x
			- m->sector[m->ennemy[x].sector].dot[s].x;
		i.yd = m->sector[m->ennemy[x].sector].dot[s + 1].y
			- m->sector[m->ennemy[x].sector].dot[s].y;
		m->ennemy[x].move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd)
			/ (i.xd * i.xd + i.yd * i.yd);
		m->ennemy[x].move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd)
			/ (i.xd * i.xd + i.yd * i.yd);
		m->ennemy[x].moving = 0;
	}
}
