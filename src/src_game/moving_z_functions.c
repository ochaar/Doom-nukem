/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_z_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:51:57 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 21:08:12 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	check_stance_zero(t_map *m, int tmp)
{
	if (tmp < STAND)
	{
		if (tmp > CROUCH)
		{
			if (m->player.height < CROUCH)
				m->player.height = m->player.height + 0.1;
			else
				m->player.height = CROUCH;
		}
		else
			m->player.height = CRAWL;
	}
	else if (m->player.height < CROUCH - 4)
		m->player.height = m->player.height + 0.1;
	else if (m->player.height < STAND - 0.2)
		m->player.height = m->player.height + 0.3;
	else
		m->player.height = STAND;
}

void		get_height(t_map *m)
{
	int		tmp;

	tmp = m->sector[m->player.sector].ceiling
		- m->sector[m->player.sector].floor;
	if (m->player.stance == 0)
		check_stance_zero(m, tmp);
	if (m->player.stance == 1)
	{
		if (tmp < CROUCH)
			m->player.height = CRAWL;
		else if (m->player.height < CROUCH - 4)
			m->player.height = m->player.height + 0.1;
		else if (m->player.height < CROUCH - 0.2)
			m->player.height = m->player.height + 0.3;
		else
			m->player.height = CROUCH;
	}
	if (m->player.stance == 2)
		m->player.height = CRAWL;
	m->player.ground = !m->player.fall;
}

static void	check_z_speed(t_map *m, int nxtz)
{
	if (m->player.move_speed.z < 0
		&& nxtz < m->sector[m->player.sector].floor + m->player.height)
	{
		m->player.coor.z = m->sector[m->player.sector].floor
			+ m->player.height;
		if (m->player.move_speed.z <= -1.7 && m->god_mod != 1)
			m->player.hp = m->player.hp - (10 * -m->player.move_speed.z
				* -m->player.move_speed.z);
		m->player.move_speed.z = 0;
		m->player.fall = 0;
		m->player.ground = 1;
		m->player.jump = 0;
	}
	else if (m->player.move_speed.z > 0
		&& nxtz > m->sector[m->player.sector].ceiling)
	{
		m->player.move_speed.z = 0;
		m->player.fall = 1;
	}
}

void		is_falling(t_map *m)
{
	double	nxtz;

	if (m->player.fall == 1)
	{
		m->player.move_speed.z = m->player.move_speed.z - m->gravity;
		nxtz = m->player.coor.z + m->player.move_speed.z;
		check_z_speed(m, nxtz);
		if (m->player.fall == 1)
		{
			m->player.coor.z = m->player.coor.z + m->player.move_speed.z;
			m->player.moving = 1;
		}
	}
}
