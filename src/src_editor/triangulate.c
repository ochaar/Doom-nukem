/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:24:13 by abechet           #+#    #+#             */
/*   Updated: 2019/07/24 22:09:33 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_count		init_cpt(t_count cpt, t_lst *polygone)
{
	cpt.n = len_list(polygone);
	cpt.j0 = left_vertex(polygone, cpt.n);
	cpt.j1 = near_vertex(cpt.n, cpt.j0, 1);
	cpt.j2 = near_vertex(cpt.n, cpt.j0, -1);
	return (cpt);
}

void		recu_trian2(t_win *win, t_lstlst *tmp3, t_lst *polygone1)
{
	recursive_triangulate(win->wo, win, tmp3, polygone1);
	free_list(polygone1);
}

t_point		recu_trian3(t_lst *polygone, t_count cpt)
{
	t_point		p;

	p.p0 = get_point_in_list(polygone, cpt.j0);
	p.p1 = get_point_in_list(polygone, cpt.j1);
	p.p2 = get_point_in_list(polygone, cpt.j2);
	return (p);
}

t_lstlst	*recursive_triangulate(t_env *w, t_win *win,
	t_lstlst *tmp3, t_lst *polygone)
{
	int			*tab;
	t_point		p;
	t_count		cpt;
	t_lst		*polygone1;

	cpt.i = 0;
	cpt = init_cpt(cpt, polygone);
	tab = indice(w, win, cpt);
	p = recu_trian3(polygone, cpt);
	cpt.x = vertex_max_dist(polygone, p, tab);
	free_dot_tab(tab);
	if (cpt.x == 0)
	{
		if (!(polygone1 = new_poly(win, polygone, cpt.j1, cpt.j2)))
			clear_n_exit(w, win);
		win->triangles = stock_last_triangle(win, win->triangles, tmp3, p);
		if (len_list(polygone1) == 3)
			win->triangles = stock_triangles(win, tmp3, polygone1);
		else
			recu_trian2(win, tmp3, polygone1);
	}
	else
		win->triangles = two_poly(win, polygone, cpt, tmp3);
	return (win->triangles);
}

void		recursive_check(t_env *w, t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		recursive_triangulate(w, win, tmp2, tmp2->head);
		tmp2 = tmp2->next;
	}
}
