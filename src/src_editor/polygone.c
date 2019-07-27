/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:54:10 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 12:54:10 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lstlst	*triangles_new(t_env *w,
	t_win *win, t_lstlst *tmp3, t_lst *polygone)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		clear_n_exit(w, win);
	tmp->head = polygone;
	tmp->next = NULL;
	tmp->txtr_wall = tmp3->txtr_wall;
	tmp->txtr_ceiling = tmp3->txtr_ceiling;
	tmp->txtr_floor = tmp3->txtr_floor;
	tmp->txtr_lower_extrude = tmp3->txtr_lower_extrude;
	tmp->txtr_higher_extrude = tmp3->txtr_higher_extrude;
	return (tmp);
}

t_lstlst	*stock_triangles(t_win *win, t_lstlst *tmp3, t_lst *poly)
{
	t_lstlst	*tmp2;

	tmp2 = NULL;
	if (win->triangles == NULL)
		win->triangles = triangles_new(win->wo, win, tmp3, poly);
	else
	{
		tmp2 = win->triangles;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = triangles_new(win->wo, win, tmp3, poly);
	}
	return (win->triangles);
}

t_lstlst	*two_poly(t_win *win,
	t_lst *polygone, t_count cpt, t_lstlst *tmp3)
{
	t_lst		*polygone1;
	t_lst		*polygone2;

	if ((polygone1 = new_poly(win, polygone, cpt.j0, cpt.x)) == NULL)
		clear_n_exit(win->wo, win);
	if ((polygone2 = new_poly(win, polygone, cpt.x, cpt.j0)) == NULL)
		clear_n_exit(win->wo, win);
	if (len_list(polygone1) == 3)
		win->triangles = stock_triangles(win, tmp3, polygone1);
	else
	{
		recursive_triangulate(win->wo, win, tmp3, polygone1);
		free_list(polygone1);
	}
	if (len_list(polygone2) == 3)
		win->triangles = stock_triangles(win, tmp3, polygone2);
	else
	{
		recursive_triangulate(win->wo, win, tmp3, polygone2);
		free_list(polygone2);
	}
	return (win->triangles);
}
