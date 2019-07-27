/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:59:43 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:57:32 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		mouse_wheel_helper(t_win *win)
{
	if (win->mode == 1)
	{
		SDL_FreeCursor(win->cursor);
		if (!(win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)))
			clear_n_exit(win->wo, win);
		win->drawing = 0;
		if (win->helptxt != NULL)
			free(win->helptxt);
		win->helptxt = strdup_safe(win->wo, win, "Moving Mode");
	}
}

int			number_of_ennemy(t_win *win)
{
	t_lstast		*tmp;
	int				i;

	i = 0;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int			number_of_sprite(t_win *win)
{
	t_lstast		*tmp;
	int				i;

	i = 0;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void		on_click(t_env *w, t_win *win)
{
	int			closed;
	t_lst		*tmp;
	t_lstlst	*tmp2;
	t_lstast	*tmp3;

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
	och(w, win, tmp2, closed);
	och3(win, tmp, tmp2, tmp3);
	och5(win);
}
