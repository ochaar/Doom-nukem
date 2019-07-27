/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mode2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:48:05 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 16:48:29 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		texture_overing(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	if (win->lstlst)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->x == win->x2 && tmp->y == win->y2 && tmp2->closed == 1)
					win->texture_overed_sector = tmp2->sector;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
	}
}

void		change_texture_index_helper2(t_env *w, t_win *win)
{
	if (win->hud_box == 4)
	{
		win->slot0 = w->texturing[win->texture_index - 4];
		win->slot1 = w->texturing[win->texture_index - 3];
		win->slot2 = w->texturing[win->texture_index - 2];
		win->slot3 = w->texturing[win->texture_index - 1];
		win->slot4 = w->texturing[win->texture_index];
	}
	if (win->hud_box == 0)
		win->blackbox_x = 253;
	if (win->hud_box == 1)
		win->blackbox_x = 304;
	if (win->hud_box == 2)
		win->blackbox_x = 355;
	if (win->hud_box == 3)
		win->blackbox_x = 406;
	if (win->hud_box == 4)
		win->blackbox_x = 457;
}

void		change_texture_index_helper(t_env *w, t_win *win)
{
	if (win->hud_box == 1)
	{
		win->slot0 = w->texturing[win->texture_index - 1];
		win->slot1 = w->texturing[win->texture_index];
		win->slot2 = w->texturing[win->texture_index + 1];
		win->slot3 = w->texturing[win->texture_index + 2];
		win->slot4 = w->texturing[win->texture_index + 3];
	}
	if (win->hud_box == 2)
	{
		win->slot0 = w->texturing[win->texture_index - 2];
		win->slot1 = w->texturing[win->texture_index - 1];
		win->slot2 = w->texturing[win->texture_index];
		win->slot3 = w->texturing[win->texture_index + 1];
		win->slot4 = w->texturing[win->texture_index + 2];
	}
	if (win->hud_box == 3)
	{
		win->slot0 = w->texturing[win->texture_index - 3];
		win->slot1 = w->texturing[win->texture_index - 2];
		win->slot2 = w->texturing[win->texture_index - 1];
		win->slot3 = w->texturing[win->texture_index];
		win->slot4 = w->texturing[win->texture_index + 1];
	}
	change_texture_index_helper2(w, win);
}

void		change_texture_index(t_env *w, t_win *win)
{
	if (win->txtr_input_type == 1 || win->txtr_input_type == 2)
	{
		if (win->texture_index < 47)
			win->texture_index += 1;
		if (win->hud_box < 4)
			win->hud_box++;
	}
	if (win->txtr_input_type == 3)
	{
		if (win->texture_index > 0)
			win->texture_index -= 1;
		if (win->hud_box > 0)
			win->hud_box--;
	}
	if (win->hud_box == 0)
	{
		win->slot0 = w->texturing[win->texture_index];
		win->slot1 = w->texturing[win->texture_index + 1];
		win->slot2 = w->texturing[win->texture_index + 2];
		win->slot3 = w->texturing[win->texture_index + 3];
		win->slot4 = w->texturing[win->texture_index + 4];
	}
	change_texture_index_helper(w, win);
}
