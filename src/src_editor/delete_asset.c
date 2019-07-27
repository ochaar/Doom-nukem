/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_asset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 09:10:03 by abechet           #+#    #+#             */
/*   Updated: 2019/06/25 09:10:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	delete_asset_helper2(t_win *win, t_lstast *current,
			t_lstast *next, t_lstast *previous)
{
	if (previous)
		previous->next = next;
	free(current);
	current = NULL;
	if (previous == NULL && next == NULL)
		win->lstast = NULL;
	if (win->lstast == NULL)
	{
		if (previous == NULL && next != NULL)
			win->lstast = next;
	}
}

void	delete_asset_helper(t_win *win, t_lstast *tmp, int j, int i)
{
	t_lstast	*current;
	t_lstast	*previous;
	t_lstast	*next;

	current = NULL;
	previous = NULL;
	next = NULL;
	win->tmpasset = NULL;
	current = tmp;
	next = current->next;
	if (j > 0)
	{
		previous = win->lstast;
		while (i < j - 1)
		{
			previous = previous->next;
			i++;
		}
	}
	if (j == 0)
		win->lstast = NULL;
	delete_asset_helper2(win, current, next, previous);
	tmp = NULL;
}

void	delete_asset(t_win *win)
{
	t_lstast	*tmp;
	int			i;
	int			j;

	tmp = NULL;
	i = 0;
	j = 0;
	tmp = win->lstast;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
			delete_asset_helper(win, tmp, j, i);
		if (tmp)
		{
			tmp = tmp->next;
			j++;
		}
	}
}
