/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:25:59 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/24 17:39:21 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		print_weapon_no_aim(t_env *w, t_map *m)
{
	t_img	img;

	if (m->player.moving != 0 && m->player.jump == 0
		&& m->player.refresh == 0)
	{
		img = fill_t_img(((m->weap[PH].sprt[2].sx + m->player.bal) * WBW),
			(m->weap[PH].sprt[2].sy + 60 - vabs(m->player.bal / 2)) * HBH,
				(m->weap[PH].sprt[2].w * WBW), (m->weap[PH].sprt[2].h * HBH));
		sprt_to_screen(w, m->weap[PH].sprt[2], img);
	}
	else if (m->player.moving != 0 && m->player.refresh == 0)
	{
		img = fill_t_img((m->weap[PH].sprt[2].sx * WBW),
			(m->weap[PH].sprt[2].sy * HBH + 1), (m->weap[PH].sprt[2].w
				* WBW), (m->weap[PH].sprt[2].h * HBH));
		sprt_to_screen(w, m->weap[PH].sprt[2], img);
	}
	else
	{
		img = fill_t_img((m->weap[PH].sprt[0].sx * WBW),
			(m->weap[PH].sprt[0].sy * HBH + 1), (m->weap[PH].sprt[0].w
				* WBW), (m->weap[PH].sprt[0].h * HBH));
		sprt_to_screen(w, m->weap[PH].sprt[0], img);
	}
}

void		print_weapon(t_env *w, t_map *m)
{
	t_img	img;

	if (m->player.aiming == 1)
	{
		img = fill_t_img((m->weap[PH].sprt[1].sx * WBW),
			(m->weap[PH].sprt[1].sy * HBH + 1), (m->weap[PH].sprt[1].w
				* WBW), (m->weap[PH].sprt[1].h * HBH));
		sprt_to_screen(w, m->weap[PH].sprt[1], img);
	}
	else
		print_weapon_no_aim(w, m);
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
		img = fill_t_img((m->weap[PH].sprt[0].sx * WBW),
			((m->weap[PH].sprt[0].sy + m->player.switching) * HBH + 1),
				(m->weap[PH].sprt[0].w * WBW), (m->weap[PH].sprt[0].h * HBH));
		sprt_to_screen(w, m->weap[PH].sprt[0], img);
	}
	if (m->player.switching > 0)
		m->player.switching = m->player.switching - 10;
}
