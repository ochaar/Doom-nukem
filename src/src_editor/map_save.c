/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:51:32 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:58:53 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		new_clockwise(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_dot		p0;
	t_dot		p1;
	t_dot		m;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;
		p0.x = tmp->x;
		p0.y = tmp->y;
		p1.x = tmp->next->x;
		p1.y = tmp->next->y;
		m.x = tmp->next->next->x;
		m.y = tmp->next->next->y;
		if (pointside2(m, p0, p1.x, p1.y) >= 0)
			tmp2->clockwise = 1;
		else
			tmp2->clockwise = 2;
		tmp2 = tmp2->next;
	}
}

void		everything_is_a_triangle(t_env *w, t_win *win)
{
	recursive_check(w, win);
	sort_triangles_points(w, win);
	check4(win);
	new_clockwise(win);
	triangulate_all_assets(win);
}

int			map_save_helper(t_win *win)
{
	t_lstlst	*tmp2;
	int			len;
	int			z;

	z = -1;
	tmp2 = win->lstlst;
	if (sector_minimum_needed_point(win) != 0)
	{
		ft_putendl("A sector is at least a triangle");
		return (0);
	}
	while (tmp2)
	{
		if (tmp2)
		{
			if (tmp2->closed)
				z = tmp2->sector;
		}
		tmp2 = tmp2->next;
	}
	len = len_listlist(win->lstlst);
	if (len - 1 == z)
		return (1);
	return (0);
}

void		map_save(t_win *win, t_env *w)
{
	if (map_save_helper(win) == 1)
	{
		everything_is_a_triangle(w, win);
		if (correct_map(win) == 0)
		{
			if (!(win->cursor = SDL_CreateSystemCursor(ARROW)))
				clear_n_exit(w, win);
			SDL_SetCursor(win->cursor);
			fit_to_game(w);
			main_pic(w, 1);
			fill_buffer(w, win);
			ft_putendl("Map saved");
			clear_n_exit(w, win);
		}
	}
	win->number = 0;
	win->same_dots = 0;
	win->index_dot = 0;
	win->tab_index = 0;
	win->triangle_sector = 0;
}
