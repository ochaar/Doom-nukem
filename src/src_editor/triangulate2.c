/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 02:20:48 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 02:21:02 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lstlst	*fill_link(t_env *w, t_win *win,
	t_lstlst *tmp3, t_point point)
{
	t_lstlst	*tmp;
	t_lst		*l0;
	t_lst		*l1;
	t_lst		*l2;

	l0 = polylstnew(win, point.p0);
	l1 = polylstnew(win, point.p1);
	l2 = polylstnew(win, point.p2);
	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		clear_n_exit(w, win);
	tmp->head = l0;
	tmp->head->next = l1;
	tmp->head->next->next = l2;
	tmp->head->next->next->next = NULL;
	tmp->next = NULL;
	tmp->txtr_wall = tmp3->txtr_wall;
	tmp->txtr_ceiling = tmp3->txtr_ceiling;
	tmp->txtr_floor = tmp3->txtr_floor;
	tmp->txtr_lower_extrude = tmp3->txtr_lower_extrude;
	tmp->txtr_higher_extrude = tmp3->txtr_higher_extrude;
	return (tmp);
}

t_lstlst	*stock_last_triangle(t_win *win,
	t_lstlst *triangle, t_lstlst *tmp3, t_point p)
{
	t_lstlst	*tmp2;

	tmp2 = NULL;
	if (triangle == NULL)
		triangle = fill_link(win->wo, win, tmp3, p);
	else
	{
		tmp2 = triangle;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = fill_link(win->wo, win, tmp3, p);
	}
	return (triangle);
}
