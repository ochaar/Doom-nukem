/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:36:59 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 20:25:39 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		free_list(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*current;

	tmp = lst;
	current = lst;
	while (current)
	{
		current = current->next;
		free(tmp);
		tmp = NULL;
		tmp = current;
	}
}

void		free_listlist(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*current;

	tmp2 = win->lstlst;
	current = tmp2;
	while (current)
	{
		free_list(tmp2->head);
		current = current->next;
		free(tmp2);
		tmp2 = NULL;
		tmp2 = current;
	}
	win->lstlst = NULL;
	win->lst = NULL;
	win->tmp = NULL;
	win->sector = 0;
	win->link = 0;
}

void		free_triangles(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*current;

	tmp2 = win->triangles;
	current = tmp2;
	while (current)
	{
		free_list(tmp2->head);
		current = current->next;
		free(tmp2);
		tmp2 = NULL;
		tmp2 = current;
	}
	win->triangles = NULL;
}

void		free_assets(t_win *win)
{
	t_lstast	*tmp2;
	t_lstast	*current;

	tmp2 = win->lstast;
	current = tmp2;
	while (current)
	{
		current = current->next;
		free(tmp2);
		tmp2 = NULL;
		tmp2 = current;
	}
	win->lstast = NULL;
	win->tmpasset = NULL;
}

void		free_dot_tab(int *dot_tab)
{
	if (dot_tab != NULL)
	{
		free(dot_tab);
		dot_tab = NULL;
	}
}
