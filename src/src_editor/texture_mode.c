/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:39:03 by abechet           #+#    #+#             */
/*   Updated: 2019/07/19 16:58:32 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		inventory_display(t_env *w, t_win *win)
{
	t_img img;

	img = fill_t_img(250, 640, 250, 66);
	img_to_screen(w, win->inventory, img);
	img = fill_t_img(253, 655, 40, 40);
	img_to_screen(w, win->slot0, img);
	img = fill_t_img(304, 655, 40, 40);
	img_to_screen(w, win->slot1, img);
	img = fill_t_img(355, 655, 40, 40);
	img_to_screen(w, win->slot2, img);
	img = fill_t_img(406, 655, 40, 40);
	img_to_screen(w, win->slot3, img);
	img = fill_t_img(457, 655, 40, 40);
	img_to_screen(w, win->slot4, img);
	img = fill_t_img(win->blackbox_x, 645, 40, 58);
	img_to_screen(w, win->blackbox, img);
}

void		help_text(t_env *w, t_win *win)
{
	if (win->texture_choice == 0)
		type_str(w, win->dst11, "Wall", 0xFF00FF);
	if (win->texture_choice == 1)
		type_str(w, win->dst11, "Ceiling", 0xFF00FF);
	if (win->texture_choice == 2)
		type_str(w, win->dst11, "Floor", 0xFF00FF);
	if (win->texture_choice == 3)
		type_str(w, win->dst11, "Lower Extrude", 0xFF00FF);
	if (win->texture_choice == 4)
		type_str(w, win->dst11, "Higher Extrude", 0xFF00FF);
}

void		thumbnail(t_env *w, t_win *win)
{
	t_lstlst	*tmp2;
	t_texture	tmp;
	t_img		img;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == win->texture_overed_sector)
			break ;
		tmp2 = tmp2->next;
	}
	if (win->texture_choice == 0)
		tmp = w->texturing[tmp2->txtr_wall];
	if (win->texture_choice == 1)
		tmp = w->texturing[tmp2->txtr_ceiling];
	if (win->texture_choice == 2)
		tmp = w->texturing[tmp2->txtr_floor];
	if (win->texture_choice == 3)
		tmp = w->texturing[tmp2->txtr_lower_extrude];
	if (win->texture_choice == 4)
		tmp = w->texturing[tmp2->txtr_higher_extrude];
	img = fill_t_img(10, 270, 96, 96);
	img_to_screen(w, win->building_hud, img);
	img = fill_t_img(15, 275, 85, 85);
	img_to_screen(w, tmp, img);
}

void		texture_mode_helper(t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == win->texture_overed_sector)
			break ;
		tmp2 = tmp2->next;
	}
	if (tmp2)
	{
		if (win->texture_choice == 0)
			tmp2->txtr_wall = win->texture_index;
		if (win->texture_choice == 1)
			tmp2->txtr_ceiling = win->texture_index;
		if (win->texture_choice == 2)
			tmp2->txtr_floor = win->texture_index;
		if (win->texture_choice == 3)
			tmp2->txtr_lower_extrude = win->texture_index;
		if (win->texture_choice == 4)
			tmp2->txtr_higher_extrude = win->texture_index;
	}
}

void		texture_mode(t_env *w, t_win *win)
{
	texture_overing(win);
	inventory_display(w, win);
	if (win->put_texture)
		texture_mode_helper(win);
	if (win->texture_overed_sector != -1)
	{
		thumbnail(w, win);
		help_text(w, win);
	}
	win->put_texture = 0;
}
