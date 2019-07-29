/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:36:02 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:32:18 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	overing(t_win *win)
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
					win->overed_sector = tmp2->sector;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
	}
}

void	delete_sector(t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*current;
	t_lstlst	*previous;
	t_lstlst	*next;

	tmp = NULL;
	current = NULL;
	previous = NULL;
	next = NULL;
	if (win->lstlst && win->overed_sector != -1)
	{
		current = win->lstlst;
		while (current->sector != win->overed_sector)
			current = current->next;
		next = current->next;
		if (win->overed_sector > 0)
		{
			previous = win->lstlst;
			while (previous->sector < win->overed_sector - 1)
				previous = previous->next;
		}
		tmp = current->head;
		if (tmp)
			free_list(tmp);
		current->head = NULL;
		free(current);
		current = NULL;
		win->link -= 1;
		win->sector -= 1;
		if (previous)
			previous->next = next;
		if (previous == NULL && next == NULL)
		{
			win->lstlst = NULL;
			win->lst = NULL;
			win->tmp = NULL;
			win->sector = 0;
			win->link = 0;
		}
		if (previous == NULL && next != NULL)
			win->lstlst = next;
		while (next)
		{
			next->sector -= 1;
			next = next->next;
		}
		win->overed_sector = -1;
	}
}

void		delete_sector2(t_win *win, t_lstlst *current, t_lstlst *previous)
{
	t_lst		*tmp;

	tmp = NULL;
	if (win->lstlst)
	{
		free(current);
		current = NULL;
		win->link -= 1;
		if (previous)
			previous->next = NULL;
		if (previous == NULL)
		{
			win->lstlst = NULL;
			win->lst = NULL;
			win->tmp = NULL;
			win->sector = 0;
			win->link = 0;
		}
		else
			win->drawing = 0;
	}
}
