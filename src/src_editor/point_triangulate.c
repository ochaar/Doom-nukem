/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_triangulate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:20:47 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 13:24:54 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	pointside2(t_dot m, t_dot p0, double x1, double y1)
{
	return (v_c_p(x1 - p0.x, y1 - p0.y, m.x - p0.x, m.y - p0.y));
}

int		point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (pointside2(m, p0, p1.x, p1.y) >= 0)
	{
		if (pointside2(m, p0, p1.x, p1.y) >= 0
		&& pointside2(m, p1, p2.x, p2.y) >= 0
		&& pointside2(m, p2, p0.x, p0.y) >= 0)
			return (1);
	}
	else
	{
		if (pointside2(m, p0, p1.x, p1.y) <= 0
		&& pointside2(m, p1, p2.x, p2.y) <= 0
		&& pointside2(m, p2, p0.x, p0.y) <= 0)
			return (1);
	}
	return (0);
}

int		len_list(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_dot	get_point_in_list(t_lst *polygone, int index)
{
	t_dot	p;
	t_lst	*tmp;
	int		i;

	i = 0;
	p.x = -1;
	p.y = -1;
	tmp = polygone;
	if (tmp)
	{
		while (i < index)
		{
			if (tmp == NULL)
				return (p);
			tmp = tmp->next;
			i++;
		}
		p.x = tmp->x;
		p.y = tmp->y;
	}
	return (p);
}

int		*indice(t_env *w, t_win *win, t_count cpt)
{
	int		*tab;

	if (!(tab = (int *)malloc(sizeof(int) * 3)))
		clear_n_exit(w, win);
	tab[0] = cpt.j0;
	tab[1] = cpt.j1;
	tab[2] = cpt.j2;
	return (tab);
}
