/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:46:06 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 18:25:31 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ramassage(t_map *m)
{
	int i;

	i = 0;
	while (i < m->sprite_map_count)
	{
		if (m->sprt[i].range >= 1
			&& ft_strcmp(m->sprite[m->sprt[i].index].type, "item") == 0)
		{
			m->player.take[m->sprt[i].index] = 1;
			m->sprt[i].taken = 1;
		}
		i++;
	}
}

void		switch_weapon(t_map *m, int i)
{
	m->player.handed = i;
	m->player.switching = 300;
}

void		shoot(t_env *w, t_map *m)
{
	if (w->dtime.shootime > (Uint32)m->weap[PH].firerate)
	{
		w->dtime.shootime = 0;
		if (m->weap[PH].actu_ammo > 0 && Mix_Playing(1) == 0)
		{
			m->player.firing = 1;
			Mix_PlayChannel(3, m->weap[PH].shoot, 0);
			m->weap[PH].actu_ammo -= 1;
		}
		else if (m->weap[PH].actu_ammo == 0)
			Mix_PlayChannel(4, w->sound.clic, 0);
	}
}

void		reload_weapon(t_env *w, t_map *m)
{
	if (Mix_Playing(3) == 0 && m->weap[PH].actu_ammo != m->weap[PH].magazine)
	{
		if (PH == 1 && m->player.bullet[1] > 0)
		{
			while (m->weap[PH].actu_ammo < m->weap[PH].magazine
				&& m->player.bullet[1] > 0)
			{
				m->player.bullet[1]--;
				m->weap[PH].actu_ammo++;
			}
			Mix_PlayChannel(1, w->sound.reload, 0);
		}
		else if (PH != 1 && m->player.bullet[0] > 0)
		{
			while (m->weap[PH].actu_ammo < m->weap[PH].magazine
				&& m->player.bullet[0] > 0)
			{
				m->player.bullet[0]--;
				m->weap[PH].actu_ammo++;
			}
			Mix_PlayChannel(1, w->sound.reload, 0);
		}
	}
}

void		get_that_time(t_env *w)
{
	Uint32		result;

	w->invert = -w->invert;
	w->random = 1.3 * (double)rand() / (double)RAND_MAX - 0.3;
	w->dtime.otime = w->dtime.ctime;
	w->dtime.ctime = SDL_GetTicks();
	result = w->dtime.ctime - w->dtime.otime;
	if (result != 0)
		w->dtime.fps = 1000 / result;
	w->dtime.etime = w->dtime.etime + result;
	w->dtime.shootime = w->dtime.shootime + result;
	w->dtime.stime = w->dtime.stime + result;
	w->dtime.walk += result;
	w->dtime.dead += result;
	if (w->dtime.stime > 1000)
		w->dtime.stime = 0;
	if (w->dtime.walk > 500)
		w->dtime.walk = 0;
	if (w->dtime.dead > 200)
		w->dtime.dead = 0;
}
