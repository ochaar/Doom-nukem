/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:05:40 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 16:52:55 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		affichage(t_env *w, t_map *m)
{
	if (KEY == SDLK_i)
	{
		if (m->player.hud != 1)
			m->player.hud = 1;
		else
			m->player.hud = 0;
	}
	if (KEY == SDLK_TAB)
	{
		if (m->player.display != 1)
			m->player.display = 1;
		else
			m->player.display = 0;
	}
	if (KEY == SDLK_m)
	{
		if (m->player.minimap != 1)
			m->player.minimap = 1;
		else
			m->player.minimap = 0;
	}
	if (KEY == SDLK_f)
		ramassage(m);
}

void		music(t_env *w)
{
	if (KEY == SDLK_p)
	{
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
	if (KEY == SDLK_KP_PLUS)
	{
		w->sound.volume += 5;
		w->sound.volume = (int)vmid(0, w->sound.volume, 128);
		Mix_VolumeMusic(w->sound.volume);
	}
	if (KEY == SDLK_KP_MINUS)
	{
		w->sound.volume -= 5;
		w->sound.volume = (int)vmid(0, w->sound.volume, 128);
		Mix_VolumeMusic(w->sound.volume);
	}
}

void		sit_down(t_env *w, t_map *m)
{
	if (KEY == SDLK_LCTRL)
	{
		m->player.stance = 1;
		m->player.fall = 1;
	}
	if (KEY == SDLK_z)
	{
		if (m->player.stance != 2)
			m->player.stance = 2;
		else
			m->player.stance = 0;
		m->player.fall = 1;
	}
	if (KEY == SDLK_x)
	{
		if (m->player.stance != 1)
			m->player.stance = 1;
		else
			m->player.stance = 0;
		m->player.fall = 1;
	}
}

void		keydown_events(t_env *w, t_map *m)
{
	if (KEY == SDLK_1)
		switch_weapon(m, 0);
	if (KEY == SDLK_2)
		switch_weapon(m, 1);
	if (KEY == SDLK_3)
		switch_weapon(m, 2);
	if (KEY == SDLK_r)
		reload_weapon(w, m);
	if (KEY == SDLK_k)
	{
		w->sequential_frame = 1;
		sequential_frame(w, m);
	}
	sit_down(w, m);
	music(w);
	affichage(w, m);
	move_floor_ceiling(w, m);
}
