/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:50:55 by abechet           #+#    #+#             */
/*   Updated: 2019/06/05 10:51:08 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			draw_asset_points(t_env *w, int i, int j, int color)
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

static void		init_helper(t_win *win)
{
	win->dst9.x = 0;
	win->dst9.y = 0;
	win->dst10.x = 300;
	win->dst10.y = 300;
	win->dst11.x = 120;
	win->dst11.y = 310;
	win->dst12.x = 10;
	win->dst12.y = 10;
	win->dst13.x = 40;
	win->dst13.y = 10;
	win->h_win_tmp = 0;
	win->w_win_tmp = 0;
	win->w_win = WIN_X;
	win->h_win = WIN_Y;
}

void			init_dst(t_win *win)
{
	win->helptxt = NULL;
	win->dst.x = 250;
	win->dst.y = 20;
	win->dst2.x = 0;
	win->dst2.y = 0;
	win->dst3.x = (WIN_X / 2 - 370 / 8);
	win->dst3.y = (WIN_Y - 305);
	win->dst4.x = 0;
	win->dst4.y = 0;
	win->dst5.x = 500;
	win->dst5.y = 655;
	win->dst6.x = WIN_X - 90;
	win->dst6.y = WIN_Y - 50;
	win->dst7.x = WIN_X - 70;
	win->dst7.y = WIN_Y - 50;
	win->dst8.x = WIN_X - 60;
	win->dst8.y = WIN_Y - 45;
	init_helper(win);
}

void			och5(t_win *win)
{
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

void			draw_grid(t_env *w)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (j < WIN_Y * 10)
	{
		i = 0;
		x = 0;
		while (i < WIN_X * 10)
		{
			set_txtr_pix(w, i, j, 0xFF36E2D7);
			i += 10;
			x++;
		}
		j += 10;
		y++;
	}
}
