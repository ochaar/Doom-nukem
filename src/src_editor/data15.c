/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data15.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:03:53 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 20:25:13 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		triangles_neighbours_helper(t_win *win, int i, int *ts1, int *ts2)
{
	if (i == 0)
	{
		if (ts1[0] == ts2[0] || ts1[0] == ts2[1] || ts1[0] == ts2[2])
			win->neighbour_index++;
		if (ts1[1] == ts2[0] || ts1[1] == ts2[1] || ts1[1] == ts2[2])
			win->neighbour_index++;
	}
	if (i == 1)
	{
		if (ts1[1] == ts2[0] || ts1[1] == ts2[1] || ts1[1] == ts2[2])
			win->neighbour_index++;
		if (ts1[2] == ts2[0] || ts1[2] == ts2[1] || ts1[2] == ts2[2])
			win->neighbour_index++;
	}
	if (i == 2)
	{
		if (ts1[2] == ts2[0] || ts1[2] == ts2[1] || ts1[2] == ts2[2])
			win->neighbour_index++;
		if (ts1[0] == ts2[0] || ts1[0] == ts2[1] || ts1[0] == ts2[2])
			win->neighbour_index++;
	}
}

int			triangles_neighbours(t_win *win, t_lstlst *tmp2, int i)
{
	t_lstlst	*tmp3;
	int			*tab_sector1;
	int			*tab_sector2;
	int			swap;

	tab_sector1 = tab_sector3(win, tmp2->sector);
	if (tmp2->clockwise == 2)
	{
		swap = tab_sector1[1];
		tab_sector1[1] = tab_sector1[2];
		tab_sector1[2] = swap;
	}
	tmp3 = win->triangles;
	while (tmp3)
	{
		win->neighbour_index = 0;
		if (tmp3->sector != -1 && tmp3->sector != tmp2->sector)
		{
			tab_sector2 = tab_sector3(win, tmp3->sector);
			if (tmp3->clockwise == 2)
			{
				swap = tab_sector2[1];
				tab_sector2[1] = tab_sector2[2];
				tab_sector2[2] = swap;
			}
			triangles_neighbours_helper(win, i, tab_sector1, tab_sector2);
			if (win->neighbour_index == 2)
				return (tmp3->sector);
		}
		free_dot_tab(tab_sector2);
		tmp3 = tmp3->next;
	}
	free_dot_tab(tab_sector1);
	return (-1);
}

void		check4(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp->nb != tmp->next->nb && tmp->next->nb != tmp->next->next->nb
			&& tmp->next->next->nb != tmp->nb)
		{
			tmp2->sector = win->triangle_sector;
			win->triangle_sector += 1;
		}
		else
			tmp2->sector = -1;
		while (tmp)
		{
			tmp->sector = tmp2->sector;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}
