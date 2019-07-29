/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:09:03 by abechet           #+#    #+#             */
/*   Updated: 2019/06/18 10:09:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ret_neighbour_sector(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
}

int		check_segment(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (1);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int		which_sector_neighbour(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
}
