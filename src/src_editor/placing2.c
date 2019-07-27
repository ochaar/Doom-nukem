/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:29:34 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 16:21:37 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lstast	*lstastnew(t_env *w, t_win *win, int sector)
{
	t_lstast	*tmp;

	if (!(tmp = (t_lstast *)malloc(sizeof(t_lstast))))
		clear_n_exit(w, win);
	tmp->x = win->x2;
	tmp->y = win->y2;
	tmp->sector = sector;
	tmp->asset_type = win->asset;
	tmp->next = NULL;
	return (tmp);
}

void		placing(t_win *win)
{
	win->dst9.y = win->y2 - 35;
	if (win->asset == 0)
		win->dst9.x = win->x2 - 25;
	if (win->asset == 1)
		win->dst9.x = win->x2 - 105;
	if (win->asset == 2)
		win->dst9.x = win->x2 - 105;
	if (win->asset == 3)
		win->dst9.x = win->x2 - 25;
	if (win->asset == 4)
		win->dst9.x = win->x2 - 15;
	if (win->asset == 5)
		win->dst9.x = win->x2 - 25;
	if (win->asset == 6)
		win->dst9.x = win->x2 - 55;
	if (win->asset == 7)
		win->dst9.x = win->x2 - 25;
	if (win->asset == 8)
		win->dst9.x = win->x2 - 25;
}

void		pick_asset(t_env *w, t_win *win)
{
	win->asset += 1;
	if (win->asset > 8)
		win->asset = 0;
	if (win->asset == 0)
		win->asset_sprite = w->m->sprite[23];
	if (win->asset == 1)
		win->asset_sprite = w->m->sprite[0];
	if (win->asset == 2)
		win->asset_sprite = w->m->sprite[1];
	if (win->asset == 3)
		win->asset_sprite = w->m->sprite[8];
	if (win->asset == 4)
		win->asset_sprite = w->m->sprite[5];
	if (win->asset == 5)
		win->asset_sprite = w->m->sprite[2];
	if (win->asset == 6)
		win->asset_sprite = w->m->sprite[3];
	if (win->asset == 7)
		win->asset_sprite = w->m->sprite[4];
	if (win->asset == 8)
		win->asset_sprite = w->m->sprite[14];
}

void		asset_overing_helper(t_env *w, t_win *win, t_lstast *tmp)
{
	if (tmp->asset_type == 1)
		win->asset_tmp = w->m->sprite[0];
	if (tmp->asset_type == 2)
		win->asset_tmp = w->m->sprite[1];
	if (tmp->asset_type == 3)
		win->asset_tmp = w->m->sprite[8];
	if (tmp->asset_type == 4)
		win->asset_tmp = w->m->sprite[5];
	if (tmp->asset_type == 5)
		win->asset_tmp = w->m->sprite[2];
	if (tmp->asset_type == 6)
		win->asset_tmp = w->m->sprite[3];
	if (tmp->asset_type == 7)
		win->asset_tmp = w->m->sprite[4];
	if (tmp->asset_type == 8)
		win->asset_tmp = w->m->sprite[14];
}

void		asset_overing(t_env *w, t_win *win)
{
	t_lstast	*tmp;
	t_img		img;

	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
		{
			if (tmp->asset_type == 0)
			{
				win->asset_tmp = w->m->sprite[23];
				set_params(w, win);
			}
			asset_overing_helper(w, win, tmp);
			img = fill_t_img(tmp->x - 25, tmp->y - 75, 0, 64);
			sprt_to_screen(w, win->asset_tmp, img);
		}
		tmp = tmp->next;
	}
}
