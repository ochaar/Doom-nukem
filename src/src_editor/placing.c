/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:48:05 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 16:20:49 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		place_asset(t_env *w, t_win *win)
{
	t_lstast	*tmp;

	if (win->lstast == NULL)
		win->lstast = lstastnew(w, win, 0);
	else
	{
		tmp = win->lstast;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lstastnew(w, win, 0);
	}
	win->place = 0;
}

int			check_first_player_start(t_win *win)
{
	t_lstast	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			ret = -1;
		tmp = tmp->next;
	}
	return (ret);
}

int			check_max_number_ennemy(t_win *win)
{
	t_lstast	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			ret++;
		tmp = tmp->next;
	}
	if (ret == 30)
		ft_putendl("Too many ennemies");
	return (ret);
}

int			check_max_number_sprite(t_win *win)
{
	t_lstast	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstast;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	if (ret == 60)
		ft_putendl("Too many items");
	return (ret);
}

void		mode(t_env *w, t_win *win)
{
	int		ret;
	int		ret2;
	t_img	img;

	ret = 0;
	ret2 = 0;
	if (win->mode == 2)
	{
		placing(win);
		if (win->check_textures == 0)
		{
			img = fill_t_img(win->dst9.x - 10, win->dst9.y - 75, 0, 96);
			sprt_to_screen(w, win->asset_sprite, img);
		}
		if (win->place == 1)
		{
			if (win->asset == 0)
				ret = check_first_player_start(win);
			ret2 = check_max_number_ennemy(win);
			if (ret == 0 && ret2 < 30 && check_max_number_sprite(win) < 60)
				place_asset(w, win);
			else
				win->place = 0;
		}
	}
}
