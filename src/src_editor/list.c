/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:29:41 by abechet           #+#    #+#             */
/*   Updated: 2019/06/06 10:29:57 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lstlst	*lstlstnew(t_env *w, t_win *win)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		clear_n_exit(w, win);
	tmp->sector = win->sector;
	tmp->closed = 0;
	tmp->head = win->lst;
	tmp->next = NULL;
	win->link += 1;
	tmp->txtr_wall = 0;
	tmp->txtr_ceiling = 1;
	tmp->txtr_floor = 0;
	tmp->txtr_lower_extrude = 0;
	tmp->txtr_higher_extrude = 0;
	return (tmp);
}

void		sector_confirm(t_win *win)
{
	win->lst = NULL;
	win->sector += 1;
	win->drawing = 0;
}

int			check_list(t_env *w, t_win *win, t_lst *lst, t_dot dot)
{
	t_lst	*tmp;
	t_lst	*new;
	int		closed;
	t_dot	dot2;

	tmp = lst;
	closed = 0;
	dot2 = fill_t_dot(dot.x, dot.y);
	new = lstnew(w, win, dot2, win->sector);
	if (dot.x == win->lst->x && dot.y == win->lst->y && win->lst->next != NULL)
	{
		sector_confirm(win);
		closed = 1;
	}
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (closed);
}

t_lst		*lstnew(t_env *w, t_win *win, t_dot dot, int sector)
{
	t_lst	*tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		clear_n_exit(w, win);
	tmp->x = dot.x;
	tmp->y = dot.y;
	tmp->sector = sector;
	tmp->next = NULL;
	return (tmp);
}
