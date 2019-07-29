/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:25:59 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 15:54:47 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fire_no_aim(t_env *w, t_map *m)
{
	t_img	img;

	img.w = m->fire.w * WIDTH / BASEWIDTH;
	img.h = m->fire.h * HEIGHT / BASEHEIGHT;
	if (m->player.handed == 0 || m->player.handed == 2)
	{
		img.x = WIDTH / 2 - (m->fire.w * WIDTH / BASEWIDTH) / 2 + (56 * WIDTH / BASEWIDTH);
		img.y = HEIGHT / 2 - ((m->fire.h * HEIGHT / BASEHEIGHT) / 2) + (67 * HEIGHT / BASEHEIGHT);
		img_to_screen(w, m->fire, img);
	}
	else if (m->player.handed == 1)
	{
		img.x = WIDTH / 2 - (m->fire.w * WIDTH / BASEWIDTH) / 2 + (45 * WIDTH / BASEWIDTH);
		img.y = HEIGHT / 2 - ((m->fire.h * HEIGHT / BASEHEIGHT) / 2) + (60 * HEIGHT / BASEHEIGHT);
		img_to_screen(w, m->fire, img);
	}
	img = fill_t_img((m->weap[PH].sprt[0].sx * WIDTH / BASEWIDTH), (m->weap[PH].sprt[0].sy + m->weap[PH].recoil) * HEIGHT / BASEHEIGHT, (m->weap[PH].sprt[0].w * WIDTH / BASEWIDTH), (m->weap[PH].sprt[0].h * HEIGHT / BASEHEIGHT));
	sprt_to_screen(w, m->weap[PH].sprt[0], img);
}

void		fire_aim(t_env *w, t_map *m)
{
	t_img	img;

	img.x = WIDTH / 2 - (m->fire.w * WIDTH / BASEWIDTH) / 2;
	img.w = m->fire.w * WIDTH / BASEWIDTH;
	img.h = m->fire.h * HEIGHT / BASEHEIGHT;
	if (m->player.handed == 0)
	{
		img.y = HEIGHT / 2 - ((m->fire.h * HEIGHT / BASEHEIGHT) / 2) + (45 * HEIGHT / BASEHEIGHT);
		img_to_screen(w, m->fire, img);
	}
	else if (m->player.handed == 1 || m->player.handed == 2)
	{
		img.y = HEIGHT / 2 - ((m->fire.h * HEIGHT / BASEHEIGHT) / 2) + (20 * HEIGHT / BASEHEIGHT);
		img_to_screen(w, m->fire, img);
	}
	img = fill_t_img((m->weap[PH].sprt[1].sx * WIDTH / BASEWIDTH), ((m->weap[PH].sprt[1].sy + (m->weap[PH].recoil / 1.5)) * HEIGHT / BASEHEIGHT), (m->weap[PH].sprt[1].w * WIDTH / BASEWIDTH), (m->weap[PH].sprt[1].h * HEIGHT / BASEHEIGHT));
	sprt_to_screen(w, m->weap[PH].sprt[1], img);	
}

void		set_fire(t_env *w, t_map *m)
{
	m->player.refresh = m->weap[PH].recoil * 2;
	m->yaw = vmid(m->yaw - m->weap[PH].dispertion, -2, 2);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
	PL_A = PL_A + m->weap[PH].dispertion / 2 * w->random;
	if (PH > -1 && m->player.firing)
	{
		if (m->player.aiming == 1)
			fire_aim(w, m);
		else
			fire_no_aim(w, m);
	}
}

void		print_weapon(t_env *w, t_map *m)
{
	t_img	img;
	int		y;
	
	y = (m->weap[PH].sprt[2].sy + 60 - vabs(m->player.bal / 2)) * HEIGHT / BASEHEIGHT;
	if (m->player.aiming == 1)
	{
		img = fill_t_img((m->weap[PH].sprt[1].sx * WIDTH / BASEWIDTH),
			(m->weap[PH].sprt[1].sy * HEIGHT / BASEHEIGHT + 1),
				(m->weap[PH].sprt[1].w * WIDTH / BASEWIDTH),
					(m->weap[PH].sprt[1].h * HEIGHT / BASEHEIGHT));
		sprt_to_screen(w, m->weap[PH].sprt[1], img);
	}
	else
	{
		if (m->player.moving != 0 && m->player.jump == 0 && m->player.refresh == 0)
		{
			img = fill_t_img(((m->weap[PH].sprt[2].sx + m->player.bal) * WIDTH / BASEWIDTH), y,
				(m->weap[PH].sprt[2].w * WIDTH / BASEWIDTH),
					(m->weap[PH].sprt[2].h * HEIGHT / BASEHEIGHT));
			sprt_to_screen(w, m->weap[PH].sprt[2], img);
		}
		else if (m->player.moving != 0 && m->player.refresh == 0)
		{
			img = fill_t_img((m->weap[PH].sprt[2].sx * WIDTH / BASEWIDTH),
				(m->weap[PH].sprt[2].sy * HEIGHT / BASEHEIGHT + 1),
					(m->weap[PH].sprt[2].w * WIDTH / BASEWIDTH),
						(m->weap[PH].sprt[2].h * HEIGHT / BASEHEIGHT));
			sprt_to_screen(w, m->weap[PH].sprt[2], img);
		}
		else
		{
			img = fill_t_img((m->weap[PH].sprt[0].sx * WIDTH / BASEWIDTH),
				(m->weap[PH].sprt[0].sy * HEIGHT / BASEHEIGHT + 1),
					(m->weap[PH].sprt[0].w * WIDTH / BASEWIDTH),
						(m->weap[PH].sprt[0].h * HEIGHT / BASEHEIGHT));
			sprt_to_screen(w, m->weap[PH].sprt[0], img);
		}
	}
}

void		hand(t_env *w, t_map *m)
{
	t_img	img;
	
	if (PH > -1 && m->player.switching == 0 && m->player.take[PH] == 1)
	{
		if (m->player.firing == 1)
			set_fire(w, m);
		else
			print_weapon(w, m);
		if (m->player.refresh > 0)
			m->player.refresh--;
	}
	else if (m->player.take[PH] == 1)
	{
		img = fill_t_img((m->weap[PH].sprt[0].sx * WIDTH / BASEWIDTH), ((m->weap[PH].sprt[0].sy + m->player.switching) * HEIGHT / BASEHEIGHT + 1), (m->weap[PH].sprt[0].w * WIDTH / BASEWIDTH), (m->weap[PH].sprt[0].h * HEIGHT / BASEHEIGHT));
		sprt_to_screen(w, m->weap[PH].sprt[0], img);
	}
	if (m->player.switching > 0)
		m->player.switching = m->player.switching - 10;
}
