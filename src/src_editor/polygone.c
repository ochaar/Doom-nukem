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

t_lstlst	*triangles_new(t_lstlst *tmp3, t_lst *polygone)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		return (NULL);
	tmp->head = polygone;
	tmp->next = NULL;
	tmp->txtr_wall = tmp3->txtr_wall;
	tmp->txtr_ceiling = tmp3->txtr_ceiling;
	tmp->txtr_floor = tmp3->txtr_floor;
	tmp->txtr_lower_extrude = tmp3->txtr_lower_extrude;
	tmp->txtr_higher_extrude = tmp3->txtr_higher_extrude;
	return (tmp);
}

t_lstlst	*stock_triangles(t_lstlst *triangles, t_lstlst *tmp3, t_lst *poly)
{
	t_lstlst	*tmp2;

	tmp2 = NULL;
	if (triangles == NULL)
		triangles = triangles_new(tmp3, poly);
	else
	{
		tmp2 = triangles;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = triangles_new(tmp3, poly);
	}
	return (triangles);
}

t_lstlst	*two_poly(t_win *win, t_lst *polygone, t_count cpt, t_lstlst *tmp3)
{
	t_lst		*polygone1;
	t_lst		*polygone2;

	if ((polygone1 = new_poly(polygone, cpt.j0, cpt.x)) == NULL)
		clear_n_exit(win, 1);
	if ((polygone2 = new_poly(polygone, cpt.x, cpt.j0)) == NULL)
		clear_n_exit(win, 1);
	if (len_list(polygone1) == 3)
		win->triangles = stock_triangles(win->triangles, tmp3, polygone1);
	else
		recursive_triangulate(win, tmp3, polygone1);
	if (len_list(polygone2) == 3)
		win->triangles = stock_triangles(win->triangles, tmp3, polygone2);
	else
		recursive_triangulate(win, tmp3, polygone2);
	return (win->triangles);
}
