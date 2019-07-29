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

void		draw_points(t_env *w, int i, int j)
{
	set_txtr_pix(w, i, j, 250240230);
	set_txtr_pix(w, i + 1, j, 250240230);
	set_txtr_pix(w, i - 1, j, 250240230);
	set_txtr_pix(w, i, j - 1, 250240230);
	set_txtr_pix(w, i + 1, j - 1, 250240230);
	set_txtr_pix(w, i - 1, j - 1, 250240230);
	set_txtr_pix(w, i, j + 1, 250240230);
	set_txtr_pix(w, i + 1, j + 1, 250240230);
	set_txtr_pix(w, i - 1, j + 1, 250240230);
}

void		draw_segments(t_env *w, t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (win->mode == 3 && tmp2->sector == win->overed_sector)
			win->color = 0xFF0000;
		else if (win->mode == 4 && tmp2->sector == win->texture_overed_sector)
			win->color = 0x00BFFF;
		else
		{
			if (tmp2->closed)
				win->color = 0x00FF00;
			else
				win->color = 0x20B2AA;
		}
		while (tmp->next)
		{
			line(w, win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);
			tmp = tmp->next;
		}
		tmp = tmp2->head;
		while (tmp)
		{
			draw_points(w, tmp->x, tmp->y);
			tmp = tmp->next;
		}
		if (win->drawing == 1)
			line(w, win, win->x1, win->y1, win->x2, win->y2);
		tmp2 = tmp2->next;
	}
	win->overed_sector = -1;
	win->texture_overed_sector = -1;
}

void		draw_triangulate(t_env *w, t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;

	tmp2 = win->triangles;
	win->color = 0xFF00FF;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next && tmp)
			{
				line(w, win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);
				tmp = tmp->next;
			}
			else
				break ;
		}
		if (tmp && tmp->next)
			line(w, win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);
		tmp2 = tmp2->next;
	}
}

void		draw_asset_points(t_env *w, int i, int j, int color)
{
	set_txtr_pix(w, i, j, color);
	set_txtr_pix(w, i + 1, j, color);
	set_txtr_pix(w, i - 1, j, color);
	set_txtr_pix(w, i + 2, j, color);
	set_txtr_pix(w, i - 2, j, color);
	set_txtr_pix(w, i, j - 1, color);
	set_txtr_pix(w, i + 1, j - 1, color);
	set_txtr_pix(w, i - 1, j - 1, color);
	set_txtr_pix(w, i - 2, j - 2, color);
	set_txtr_pix(w, i + 2, j - 2, color);
	set_txtr_pix(w, i, j + 1, color);
	set_txtr_pix(w, i + 1, j + 1, color);
	set_txtr_pix(w, i - 1, j + 1, color);
	set_txtr_pix(w, i + 2, j + 2, color);
	set_txtr_pix(w, i - 2, j + 2, color);
}

void		draw_assets(t_env *w, t_win *win)
{
	t_lstasset	*tmp;
	int			color;

	color = 707070;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			color = 707070;
		if (tmp->asset_type == 1)
			color = 0xC0C0C0;
		if (tmp->asset_type == 2)
			color = 0x800000;
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

void		on_click(t_win *win)
{
	int			closed;
	t_lst		*tmp;
	t_lstlst	*tmp2;
	t_lstasset	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	closed = 0;
	if (win->left_click)
	{
		win->changemode = 0;
		if (win->triangles)
			free_triangles(win);
	}
	if (win->mode == 3)
		overing(win);
	if (win->left_click && win->mode == 3)
	{
		delete_sector(win);
		delete_asset(win);
	}
	if (win->left_click && win->mode == 0)
	{
		if (win->lstlst == NULL)
			win->lstlst = lstlstnew(win);
		if (win->sector == win->link)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = lstlstnew(win);
		}
		win->drawing = 1;
		if (win->lst == NULL)
		{
			win->lst = lstnew(win->x1, win->y1, win->sector);
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->head = win->lst;
		}
		else
			closed = check_list(win, win->lst, win->x1, win->y1);
		if (closed)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->closed = 1;
		}
	}
	if (win->left_click == 1 && win->mode == 1)
	{
		tmp2 = win->lstlst;
		tmp3 = win->lstasset;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp && win->moving == 0)
			{
				if (tmp->x == win->x0 && tmp->y == win->y0)
				{
					win->tmp = tmp;
					win->moving = 1;
				}
				else
					tmp = tmp->next;
			}
			if (win->moving == 1)
			{
				win->tmp->x = win->x2;
				win->tmp->y = win->y2;
				if (tmp2->closed == 1)
					last_is_first(tmp2->head);
			}
			tmp2 = tmp2->next;
		}
		while (tmp3 && win->moving == 0)
		{
			if (tmp3->x == win->x0 && tmp3->y == win->y0)
			{
				win->tmpasset = tmp3;
				win->moving = 2;
			}
			else
				tmp3 = tmp3->next;
		}
		if (win->moving == 2)
		{
			if (win->tmpasset)
			{
				win->tmpasset->x = win->x2;
				win->tmpasset->y = win->y2;
			}
		}
	}
	if (win->left_click == 1 && win->mode == 2)
	{
		win->place = 1;
	}
	if (win->left_click == 1 && win->mode == 4)
	{
		win->put_texture = 1;
	}
	if (win->moving == 0)
		win->left_click = 0;
}

void		loop_play(t_env *w, t_win *win)
{
	w->stopread = 0;
	while (42 && w->stopread == 0)
	{
		SDL_WaitEvent(&win->event);
		sdl_event(w, win);
		on_click(win);
		clean_render(w, 000);
		draw_grid(w, win);
		if (win->triangles)
			draw_triangulate(w, win);
		if (win->lstlst)
			draw_segments(w, win);
		if (win->lstasset)
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
