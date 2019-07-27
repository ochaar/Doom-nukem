/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:19:59 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:58:53 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	sdl_event_mouse_wheel_helper(t_env *w, t_win *win, t_lstlst *tmp2)
{
	if (win->mode == 0)
	{
		SDL_FreeCursor(win->cursor);
		if (!(win->cursor = SDL_CreateSystemCursor(ARROW)))
			clear_n_exit(w, win);
		if (tmp2)
		{
			while (tmp2->next)
				tmp2 = tmp2->next;
			if (tmp2->closed == 0)
				win->drawing = 1;
		}
		if (win->helptxt != NULL)
			free(win->helptxt);
		win->helptxt = strdup_safe(w, win, "Drawing Mode");
	}
	mouse_wheel_helper(win);
}

static void	sdl_event_mouse_wheel_helper2(t_env *w, t_win *win)
{
	if (win->mode == 2)
	{
		SDL_FreeCursor(win->cursor);
		if (!(win->cursor = SDL_CreateSystemCursor(ARROW)))
			clear_n_exit(w, win);
		win->drawing = 0;
		if (win->helptxt != NULL)
			free(win->helptxt);
		win->helptxt = strdup_safe(w, win, "Placing Mode");
	}
	if (win->mode == 3)
	{
		SDL_FreeCursor(win->cursor);
		if (!(win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO)))
			clear_n_exit(w, win);
		win->drawing = 0;
		if (win->helptxt != NULL)
			free(win->helptxt);
		win->helptxt = strdup_safe(w, win, "Delete Mode");
	}
}

void		sdl_event_mouse_wheel(t_env *w, t_win *win, t_lstlst *tmp2)
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
	sdl_event_mouse_wheel_helper(w, win, tmp2);
	sdl_event_mouse_wheel_helper2(w, win);
	if (win->mode == 4)
	{
		SDL_FreeCursor(win->cursor);
		if (!(win->cursor = SDL_CreateSystemCursor(CROSSHAIR)))
			clear_n_exit(w, win);
		win->drawing = 0;
		if (win->helptxt != NULL)
			free(win->helptxt);
		win->helptxt = strdup_safe(w, win, "Texture Mode");
	}
}

void		sdl_event_mouse_left_click(t_win *win, int x, int y, t_lst *tmp)
{
	SDL_GetMouseState(&x, &y);
	if (win->mode == 0)
	{
		win->x1 = ft_round(x);
		win->y1 = ft_round(y);
	}
	win->x0 = ft_round(x);
	win->y0 = ft_round(y);
	win->left_click = 1;
	if (win->left_click == 1 && win->mode == 1
		&& (win->moving == 1 || win->moving == 2))
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

void		sdl_event_mouse_right_click(t_env *w, t_win *win)
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
