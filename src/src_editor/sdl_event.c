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

int				ft_round(int n)
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

static void		sdl_event_mouse(t_env *w, t_win *win)
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
		sdl_event_mouse_wheel(w, win, tmp2);
	if (win->event.button.button == SDL_BUTTON_RIGHT
		&& win->event.type == SDL_MOUSEBUTTONUP && win->moving == 0)
		sdl_event_mouse_right_click(w, win);
	if (win->event.button.button == SDL_BUTTON_LEFT
		&& win->event.type == SDL_MOUSEBUTTONUP)
		sdl_event_mouse_left_click(win, x, y, tmp);
	SDL_GetMouseState(&x, &y);
	win->x2 = ft_round(x);
	win->y2 = ft_round(y);
}

void			sdl_event(t_env *w, t_win *win)
{
	sdl_event_mouse(w, win);
	sdl_event_key(w, win);
}
