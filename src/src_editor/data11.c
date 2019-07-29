/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:56:31 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:20:47 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			number_of_dot_per_line_with_same(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	i = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
				i++;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (i);
}

int			*create_y_dot_tab(t_win *win, int y, int i)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			index;

	index = 0;
	if (!(dot_tab = (int *)malloc(sizeof(int) * (i + 1))))
		clear_n_exit(win, 1);
	// A verifier plus longuement
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				dot_tab[index] = tmp->x;
				index++;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	sort_int_tab(dot_tab, i);
	return (dot_tab);
}

int			number_of_dot_per_line(t_win *win, int y)
{
	int			*dot_tab;
	int			i;
	int			same;
	int			index;

	index = 0;
	same = 0;
	i = number_of_dot_per_line_with_same(win, y);
	dot_tab = create_y_dot_tab(win, y, i);
	if (i > 1)
	{
		while (index < i - 1)
		{
			if (dot_tab[index] == dot_tab[index + 1])
				same++;
			index++;
		}
	}
	i -= same;
	free_dot_tab(dot_tab);
	return (i);
}

int			total_exclusive_points(t_win *win)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		i += number_of_dot_per_line(win, y);
		y++;
	}
	return (i);
}
