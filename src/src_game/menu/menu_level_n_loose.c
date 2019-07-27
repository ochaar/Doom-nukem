/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_level_n_loose.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:28:01 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 08:58:49 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		event_menu_loose(t_env *w, t_map *m)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == 27)
			{
				w->menu.i = 1;
				m->game_over = 0;
				return (1);
			}
			if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
			{
				m->game_over = 0;
				m->player.hp = m->player.max_hp;
				return (2);
			}
		}
		if (w->event.type == SDL_WINDOWEVENT)
		{
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
		}
	}
	return (0);
}

int		menu_loose(t_env *w, t_map *m)
{
	int		ret;

	ret = 0;
	main_pic(w, 2);
	w->txthead = fill_t_dot(350, 400);
	type_str(w, w->txthead, "Press enter to retry", 0x12FFFFFF);
	m->newgame = 1;
	while (1)
	{
		if ((ret = event_menu_loose(w, m)) > 0)
			return (ret);
		img_update(w);
	}
	return (0);
}

int		event_menu_lvl(t_env *w)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == 27)
			{
				w->menu.i = 1;
				return (1);
			}
			if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
			{
				if (w->menu.i == 1)
					return (1);
				else
					return (0);
			}
		}
		if (w->event.type == SDL_WINDOWEVENT)
		{
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
		}
	}
	return (2);
}

int		change_lvl_type(t_env *w, t_map *m)
{
	free(w->currmap);
	if (map_is_in_core(w, m->linklvl) == 1)
	{
		type_str(w, w->txthead, CHANGELVL, 0x12FFFFFF);
		w->currmap = strdup_check(w, m->linklvl);
		w->menu.i = 5;
	}
	else
	{
		w->currmap = strdup_check(w, "hsh");
		w->menu.i = 1;
		m->change_lvl = 0;
		m->newgame = 1;
		if (ft_strcmp(m->linklvl, "end_game") == 0)
			type_str(w, w->txthead, ENDGAME, 0x12FFFFFF);
		else
			return (1);
	}
	return (0);
}

int		menu_change_lvl(t_env *w, t_map *m)
{
	int		ret;
	float	time_lvl;

	ret = 0;
	m->newgame = 1;
	m->change_lvl = 0;
	w->dtime.end_lvl = SDL_GetTicks();
	time_lvl = w->dtime.end_lvl - w->dtime.start_lvl;
	time_lvl = time_lvl / 1000;
	w->txthead = fill_t_dot(100, 400);
	main_pic(w, 1);
	if (change_lvl_type(w, m) == 1)
		return (1);
	type_str(w, w->txtnxtline, "Level completed in : ", 0x12FFFFFF);
	ft_get_time(w, time_lvl);
	type_str(w, w->txtnxtto, " seconds", 0x12FFFFFF);
	while (1)
	{
		if ((ret = event_menu_lvl(w)) < 2)
			return (ret);
		img_update(w);
	}
	return (0);
}
