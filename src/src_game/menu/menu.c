/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:45:13 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 19:09:52 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	menu_main_type(t_env *w)
{
	if (w->menu.j == 1)
		w->menu.i = 5;
	else if (w->menu.j >= 2 && w->menu.j <= 4)
		w->menu.i = w->menu.j;
	else if (w->menu.j == 5)
		w->menu.i = -1;
	else
	{
		w->menu.j = 1;
		w->menu.i = vmin(w->menu.i + 1, 2);
	}
}

void	event_menu(t_env *w)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == SDLK_ESCAPE)
			{
				w->menu.i = vmax(-1, w->menu.i - 1);
				w->m->newgame = 1;
			}
			if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
				menu_main_type(w);
			if (KEY == SDLK_UP)
				w->menu.j = ((w->menu.j - 1) < 1) ? 5 : (w->menu.j - 1);
			if (KEY == SDLK_DOWN)
				w->menu.j = ((w->menu.j + 1) > 5) ? 1 : (w->menu.j + 1);
		}
		if (w->event.type == SDL_WINDOWEVENT)
		{
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
		}
	}
}

void	main_menu(t_env *w, t_map *m)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	if (SDL_ShowCursor(SDL_ENABLE) < 0)
		set_error(w, m, 4, strdup_check(w, "SDL_ShowCursor"));
	Mix_PauseMusic();
	w->txthead = fill_t_dot(800, 550);
	w->menu.j = 1;
	while (1)
	{
		event_menu(w);
		if (w->menu.i == -1)
			exit_game(w, m, 1);
		if (w->menu.i == 0)
		{
			main_pic(w, 0);
			type_str(w, w->txthead, "press enter...", 0x12FEA800);
			w->menu.j = -1;
		}
		else if (w->menu.i == 1)
			menu_screen(w);
		else
			break ;
		img_update(w);
		get_that_time(w);
	}
}

int		launch_type(t_env *w, t_map *m)
{
	if (m->game_over == 1)
	{
		if (menu_loose(w, m) == 1)
			return (1);
	}
	else if (m->change_lvl == 1)
	{
		if (menu_change_lvl(w, m) == 1)
			return (1);
	}
	if (m->newgame == 1)
	{
		if (parse_map_in_core(w, m, w->currmap) != 0)
			return (1);
		w->dtime.start_lvl = SDL_GetTicks();
	}
	return (0);
}

void	launch(t_env *w, t_map *m)
{
	while (1)
	{
		if (w->menu.i < 2)
			main_menu(w, m);
		else if (w->menu.i == 2)
			menu_maps(w);
		else if (w->menu.i == 3)
			menu_settings(w);
		else if (w->menu.i == 4)
			level_editor_start(w);
		if (w->menu.i > 4)
		{
			if (launch_type(w, m) == 1)
				continue ;
			run(w, m);
		}
	}
}
