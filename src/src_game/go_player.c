/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:34:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 16:34:30 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		go_forward(t_map *m)
{
	m->player.movespeed = 1;
	m->player.move_speedless.x += m->player.anglecos / 3;
	m->player.move_speedless.y += m->player.anglesin / 3;
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

void		go_back(t_map *m)
{
	m->player.movespeed = 0;
	m->player.move_speedless.x -= m->player.anglecos / 5;
	m->player.move_speedless.y -= m->player.anglesin / 5;
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

void		go_left(t_map *m)
{
	m->player.movespeed = 1;
	m->player.move_speedless.x += m->player.anglesin / 3;
	m->player.move_speedless.y -= m->player.anglecos / 3;
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

void		go_right(t_map *m)
{
	m->player.movespeed = 1;
	m->player.move_speedless.x -= m->player.anglesin / 3;
	m->player.move_speedless.y += m->player.anglecos / 3;
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

void		jump(t_env *w, t_map *m)
{
	if (m->player.ground == 1 && m->player.stance == 0)
	{
		Mix_PlayChannel(2, w->sound.jump, 0);
		m->player.move_speed.z = m->player.move_speed.z + 0.8;
		m->player.fall = 1;
		m->player.jump = 1;
	}
}
