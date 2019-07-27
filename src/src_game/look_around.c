/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_around.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:35:45 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 17:02:38 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		look_left(t_map *m)
{
	PL_A = PL_A - 0.05;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		look_right(t_map *m)
{
	PL_A = PL_A + 0.05;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		look_around(t_env *w, t_map *m)
{
	PL_A = PL_A + (w->event.motion.xrel * 0.001)
		* ((double)m->player.mousesp / 100.f);
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->yaw = vmid(m->yaw + (w->event.motion.yrel * 0.002)
		* ((double)m->player.mousesp / 100.f), -2, 2);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
}

void		sprint(t_map *m)
{
	m->player.movespeed = 1.5;
	m->player.move_speedless.x += m->player.anglecos / 1.5;
	m->player.move_speedless.y += m->player.anglesin / 1.5;
	if (m->player.height <= 9.3)
	{
		m->player.move_speedless.x /= 2;
		m->player.move_speedless.y /= 2;
	}
	if (m->player.height <= 2)
	{
		m->player.move_speedless.x /= 2;
		m->player.move_speedless.y /= 2;
	}
}
