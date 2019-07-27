/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_poly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:29:19 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 13:29:40 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lst	*polylstnew(t_win *win, t_dot d)
{
	t_lst	*tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		clear_n_exit(win->wo, win);
	tmp->x = d.x;
	tmp->y = d.y;
	tmp->next = NULL;
	return (tmp);
}

t_lst	*append_poly(t_win *win, t_lst *polygone,
	t_lst *p, t_lst **tmp)
{
	if (p == NULL)
	{
		p = polylstnew(win, get_point_in_list(polygone, win->append_i));
		*tmp = p;
		if (p->x == -1 && p->y == -1)
			return (NULL);
	}
	else
	{
		while (p->next)
			p = p->next;
		p->next = polylstnew(win, get_point_in_list(polygone, win->append_i));
	}
	return (p);
}

t_lst	*new_poly(t_win *win, t_lst *polygone, int start, int end)
{
	int			n;
	t_lst		*p;
	t_lst		*tmp;

	p = NULL;
	tmp = NULL;
	n = len_list(polygone);
	win->append_i = start;
	while (win->append_i != end)
	{
		p = append_poly(win, polygone, p, &tmp);
		win->append_i = near_vertex(n, win->append_i, 1);
		if (win->append_i == -10000)
			return (p);
	}
	if (p)
	{
		while (p->next)
			p = p->next;
		p->next = polylstnew(win, get_point_in_list(polygone, win->append_i));
	}
	return (tmp);
}
