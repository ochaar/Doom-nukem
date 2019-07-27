/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:15:25 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 17:52:53 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			print_game(t_env *w, t_win *win)
{
	t_dot dot;

	dot.x = 200;
	dot.y = 50;
	if (win->changemode)
	{
		SDL_SetCursor(win->cursor);
		type_str(w, dot, win->helptxt, 0xFF00FF);
	}
	img_update(w);
	return (0);
}

int			draw_assets_helper(t_lstast *tmp)
{
	int		color;

	color = 0;
	if (tmp->asset_type == 3)
		color = 0xFF0000;
	if (tmp->asset_type == 4)
		color = 0xFFFF00;
	if (tmp->asset_type == 5)
		color = 0xD3D3D3;
	if (tmp->asset_type == 6)
		color = 0xFF69B4;
	if (tmp->asset_type == 7)
		color = 0xBDB76B;
	if (tmp->asset_type == 8)
		color = 0xF5F5F5;
	return (color);
}

void		draw_assets(t_env *w, t_win *win)
{
	t_lstast	*tmp;
	int			color;
	int			ret;

	color = 707070;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			color = 707070;
		if (tmp->asset_type == 1)
			color = 0xC0C0C0;
		if (tmp->asset_type == 2)
			color = 0x800000;
		ret = draw_assets_helper(tmp);
		if (ret != 0)
			color = ret;
		draw_asset_points(w, tmp->x, tmp->y, color);
		tmp = tmp->next;
	}
}

void		last_is_first(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->x = lst->x;
	tmp->y = lst->y;
}

void		loop_play(t_env *w, t_win *win)
{
	w->stopread = 0;
	while (42 && w->stopread == 0)
	{
		SDL_WaitEvent(&win->event);
		sdl_event(w, win);
		on_click(w, win);
		clean_render(w, 000);
		draw_grid(w);
		if (win->triangles)
		{
			win->color = 0xFF00FF;
			draw_triangulate(w, win);
		}
		if (win->lstlst)
			draw_segments(w, win);
		if (win->lstast)
			draw_assets(w, win);
		mode(w, win);
		if (win->mode != 2)
			asset_overing(w, win);
		if (win->mode == 4)
			texture_mode(w, win);
		print_game(w, win);
	}
	w->stopread = 0;
}
