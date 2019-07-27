/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:09:43 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 13:09:54 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void		draw_segments_helper2(t_lstlst *tmp2, t_win *win)
{
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
}

void		draw_segments_helper(t_env *w, t_win *win,
				t_lst *tmp, t_lstlst *tmp2)
{
	t_dot		tmp_dot;
	t_dot		tmp2_dot;

	draw_segments_helper2(tmp2, win);
	while (tmp->next)
	{
		tmp_dot = fill_t_dot(tmp->x, tmp->y);
		tmp2_dot = fill_t_dot(tmp->next->x, tmp->next->y);
		line(w, win, tmp_dot, tmp2_dot);
		tmp = tmp->next;
	}
	tmp = tmp2->head;
	while (tmp)
	{
		draw_points(w, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	if (win->drawing == 1)
	{
		tmp_dot = fill_t_dot(win->x1, win->y1);
		tmp2_dot = fill_t_dot(win->x2, win->y2);
		line(w, win, tmp_dot, tmp2_dot);
	}
}

void		draw_segments(t_env *w, t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		draw_segments_helper(w, win, tmp, tmp2);
		tmp2 = tmp2->next;
	}
	win->overed_sector = -1;
	win->texture_overed_sector = -1;
}

void		draw_triangulate(t_env *w, t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;
	t_dot		tmp_dot;
	t_dot		tmp2_dot;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next && tmp)
			{
				tmp_dot = fill_t_dot(tmp->x, tmp->y);
				tmp2_dot = fill_t_dot(tmp->next->x, tmp->next->y);
				line(w, win, tmp_dot, tmp2_dot);
				tmp = tmp->next;
			}
			else
				break ;
		}
		if (tmp && tmp->next)
			line(w, win, tmp_dot, tmp2_dot);
		tmp2 = tmp2->next;
	}
}
