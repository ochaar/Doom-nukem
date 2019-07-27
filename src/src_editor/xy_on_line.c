/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:55:47 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:55:56 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			y_min_point(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;

	y = WIN_Y;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y < y)
				y = tmp->y;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (y);
}

int			number_of_y(t_win *win, t_lstlst *tmp2, t_lst *tmp)
{
	int			y;
	int			i;

	i = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y)
				{
					i++;
					y++;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		y++;
	}
	return (i);
}

int			next_y(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	while (y <= WIN_Y)
	{
		y++;
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y)
					return (y);
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
	}
	return (-1);
}

int			x_min_on_line(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;

	x = WIN_X;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				if (tmp->x < x)
					x = tmp->x;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (x);
}

int			next_x_on_line(t_win *win, int y, int x)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	i = WIN_X;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				if (tmp->x > x && tmp->x < i)
					i = tmp->x;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (i);
}
