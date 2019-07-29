/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data12.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:57:21 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:57:42 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		sort_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;
	int			i;
	int			index;
	int			*dot_tab;

	y = WIN_Y;
	tmp = NULL;
	index = 0;
	y = y_min_point(win);
	while (y < WIN_Y)
	{
		i = number_of_dot_per_line_with_same(win, y);
		if (i > 0)
		{
			index = 0;
			dot_tab = create_y_dot_tab(win, y, i);
			while (index < i)
			{
				tmp2 = win->lstlst;
				while (tmp2)
				{
					tmp = tmp2->head;
					while (tmp)
					{
						if (tmp->y == y && tmp->x == dot_tab[index])
							tmp->nb = win->number;
						tmp = tmp->next;
					}
					tmp2 = tmp2->next;
				}
				index++;
				if (dot_tab[index] != dot_tab[index - 1])
					win->number++;
			}
		}
		y++;
	}
}

t_lstlst	*dts_helper(t_win *win, int sector)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
			break ;
		tmp2 = tmp2->next;
	}
	return (tmp2);
}

int			*dot_tab_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			i;
	int			index;

	dot_tab = NULL;
	i = 0;
	index = 0;
	tmp2 = dts_helper(win, sector);
	tmp = tmp2->head;
	i = len_list(tmp);
	if (tmp2)
	{
		if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
			clear_n_exit(win, 1);
		while (tmp)
		{
			dot_tab[index] = tmp->nb;
			index++;
			tmp = tmp->next;
		}
		sort_int_tab(dot_tab, i);
	}
	return (dot_tab);
}
