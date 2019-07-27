/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fire.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:38:56 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 17:39:17 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fire_no_aim(t_env *w, t_map *m)
{
	t_img	img;

	img.w = m->fire.w * WBW;
	img.h = m->fire.h * HBH;
	if (m->player.handed == 0 || m->player.handed == 2)
	{
		img.x = WIDTH / 2 - (m->fire.w * WBW) / 2 + (56 * WBW);
		img.y = HEIGHT / 2 - ((m->fire.h * HBH) / 2) + (67 * HBH);
		img_to_screen(w, m->fire, img);
	}
	else if (m->player.handed == 1)
	{
		img.x = WIDTH / 2 - (m->fire.w * WBW) / 2 + (45 * WBW);
		img.y = HEIGHT / 2 - ((m->fire.h * HBH) / 2) + (60 * HBH);
		img_to_screen(w, m->fire, img);
	}
	img = fill_t_img((m->weap[PH].sprt[0].sx * WBW), (m->weap[PH].sprt[0].sy
		+ m->weap[PH].recoil) * HBH, (m->weap[PH].sprt[0].w * WBW),
			(m->weap[PH].sprt[0].h * HBH));
	sprt_to_screen(w, m->weap[PH].sprt[0], img);
}

void		fire_aim(t_env *w, t_map *m)
{
	t_img	img;

	img.x = WIDTH / 2 - (m->fire.w * WBW) / 2;
	img.w = m->fire.w * WBW;
	img.h = m->fire.h * HBH;
	if (m->player.handed == 0)
	{
		img.y = HEIGHT / 2 - ((m->fire.h * HBH) / 2) + (45 * HBH);
		img_to_screen(w, m->fire, img);
	}
	else if (m->player.handed == 1 || m->player.handed == 2)
	{
		img.y = HEIGHT / 2 - ((m->fire.h * HBH) / 2) + (20 * HBH);
		img_to_screen(w, m->fire, img);
	}
	img = fill_t_img((m->weap[PH].sprt[1].sx * WBW), ((m->weap[PH].sprt[1].sy
		+ (m->weap[PH].recoil / 1.5)) * HBH), (m->weap[PH].sprt[1].w * WBW),
			(m->weap[PH].sprt[1].h * HBH));
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
