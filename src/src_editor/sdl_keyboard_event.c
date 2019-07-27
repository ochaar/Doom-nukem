/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_keyboard_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:19:20 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:58:53 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		sdl_event_key_helper(t_env *w, t_win *win)
{
	if (win->event.type == SDL_QUIT
		|| win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		if (!(win->cursor = SDL_CreateSystemCursor(ARROW)))
			clear_n_exit(w, win);
		SDL_SetCursor(win->cursor);
		fit_to_game(w);
		clear_n_exit(w, win);
		return ;
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_F5])
	{
		if (win->lstlst)
		{
			map_save(win, w);
			if (w->stopread == 1)
				return ;
		}
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_RETURN])
	{
		if (win->mode == 4)
			win->put_texture = 1;
	}
}

static void		sdl_event_key_helper2(t_win *win)
{
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_UP])
	{
		if (win->mode == 4)
		{
			win->texture_choice += 1;
			if (win->texture_choice > 4)
				win->texture_choice = 0;
		}
		if (win->mode == 1)
		{
			win->param_index += 1;
			if (win->param_index > 2)
				win->param_index = 0;
		}
	}
}

static void		sdl_event_key_helper3(t_win *win)
{
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_DOWN])
	{
		if (win->mode == 4)
		{
			win->texture_choice -= 1;
			if (win->texture_choice < 0)
				win->texture_choice = 4;
		}
		if (win->mode == 1)
		{
			win->param_index -= 1;
			if (win->param_index < 0)
				win->param_index = 2;
		}
	}
}

void			sdl_event_key(t_env *w, t_win *win)
{
	win->keystate = (Uint8 *)SDL_GetKeyboardState(0);
	sdl_event_key_helper(w, win);
	sdl_event_key_helper2(win);
	sdl_event_key_helper3(win);
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_RIGHT])
	{
		if (win->mode == 4)
		{
			win->txtr_input_type = 2;
			change_texture_index(w, win);
		}
		if (win->mode == 1)
			increase_value(win);
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_LEFT])
	{
		if (win->mode == 4)
		{
			win->txtr_input_type = 3;
			change_texture_index(w, win);
		}
		if (win->mode == 1)
			decrease_value(win);
	}
}
