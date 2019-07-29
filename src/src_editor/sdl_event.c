/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:28:53 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 18:12:27 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	ft_round(int n)
{
	int a;
	int b;
	int tmp;

	tmp = n;
	a = 0;
	b = 0;
	if (n == 0)
		return (0);
	while (n % 10 > 0)
	{
		n = n - 1;
		a++;
	}
	while (tmp % 10 > 0)
	{
		tmp = tmp + 1;
		b++;
	}
	if (a < b)
		return (n);
	return (tmp);
}

static void	sdl_event_key(t_env *w, t_win *win)
{
	win->keystate = (Uint8 *)SDL_GetKeyboardState(0);
	if (win->event.type == SDL_QUIT
		|| win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		w->stopread = 1;
		fit_to_game(w);
		return ;
		// clear_n_exit(win, 0);
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
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_K])
	{
		if (win->lstlst)
		{
			correct_intersections_in_a_sector(win);
		}
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_P])
	{
		if (win->lstlst)
		{
			everything_is_a_triangle(win);
			check_player_start(win);
		}
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_O])
	{
		if (win->lstlst)
		{
			sectors_on_top(win);
		}
	}
	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_L])
	{
		if (win->lstlst)
		{
			everything_is_a_triangle(win);
			sector_inside_sector(win);
		}
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_RETURN])
	{
		if (win->mode == 4)
			win->put_texture = 1;
	}
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

	/*if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_H])
	{
		win->helptxt = TTF_RenderText_Blended(win->police,
			"test", win->color_font_r);
		SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst6);
	}*/
}

static void	sdl_event_mouse(t_env *w, t_win *win)
{
	int			x;
	int			y;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	x = 0;
	y = 0;
	tmp = win->lst;
	tmp2 = win->lstlst;

	if (win->event.type == SDL_MOUSEWHEEL)
	{
		win->changemode = 1;
		if (win->moving == 0)
		{
			if (win->event.wheel.y > 0)
				win->mode -= 1;
			if (win->event.wheel.y < 0)
				win->mode += 1;
		}

		if (win->mode > 4)
			win->mode = 0;
		if (win->mode < 0)
			win->mode = 4;

		if (win->mode == 0)
		{
			SDL_FreeCursor(win->cursor);
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			if (tmp2)
			{
				while (tmp2->next)
					tmp2 = tmp2->next;
				if (tmp2->closed == 0)
					win->drawing = 1;
			}
			if (win->helptxt != NULL)
				free(win->helptxt);
			win->helptxt = ft_strdup("Drawing Mode");
		}

		if (win->mode == 1)
		{
			SDL_FreeCursor(win->cursor);
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			win->drawing = 0;
			if (win->helptxt != NULL)
				free(win->helptxt);
			win->helptxt = ft_strdup("Moving Mode");
		}

		if (win->mode == 2)
		{
			SDL_FreeCursor(win->cursor);
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			win->drawing = 0;
			if (win->helptxt != NULL)
				free(win->helptxt);
			win->helptxt = ft_strdup("Placing Mode");
		}

		if (win->mode == 3)
		{
			SDL_FreeCursor(win->cursor);
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
			win->drawing = 0;
			if (win->helptxt != NULL)
				free(win->helptxt);
			win->helptxt = ft_strdup("Delete Mode");
		}

		if (win->mode == 4)
		{
			SDL_FreeCursor(win->cursor);
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
			win->drawing = 0;
			if (win->helptxt != NULL)
				free(win->helptxt);
			win->helptxt = ft_strdup("Texture Mode");
		}
	}

	if (win->event.button.button == SDL_BUTTON_RIGHT
		&& win->event.type == SDL_MOUSEBUTTONUP && win->moving == 0)
	{
		if (win->mode == 0)
			undo(win);
		if (win->mode == 2)
			pick_asset(w, win);
		if (win->mode == 4)
		{
			win->txtr_input_type = 1;
			change_texture_index(w, win);
		}
	}

	if (win->event.button.button == SDL_BUTTON_LEFT
		&& win->event.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (win->mode == 0)
		{
			win->x1 = ft_round(x);
			win->y1 = ft_round(y);
			win->just_close = 0;
		}
		win->x0 = ft_round(x);
		win->y0 = ft_round(y);
		win->left_click = 1;
		if (win->left_click == 1 && win->mode == 1 && (win->moving == 1 || win->moving == 2))
		{
			win->moving = 0;
			win->tmp = NULL;
			win->tmpasset = NULL;
			win->x0 = -1;
			win->y0 = -1;
			if (win->lst)
			{
				while (tmp->next)
					tmp = tmp->next;
				win->x1 = tmp->x;
				win->y1 = tmp->y;
			}
		}
	}
	SDL_GetMouseState(&x, &y);
	win->x2 = ft_round(x);
	win->y2 = ft_round(y);
}

void		sdl_event(t_env *w, t_win *win)
{
	sdl_event_mouse(w, win);
	sdl_event_key(w, win);
}
