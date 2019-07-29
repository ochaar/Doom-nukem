/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:30:22 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 13:31:12 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		near_vertex(int n, int i, int di)
{
	if (n != 0)
		return ((n + (i + di) % n) % n);
	return (-10000);
}

int		left_vertex(t_lst *polygone, int len)
{
	t_count	cpt;
	t_lst	*tmp;
	t_dot	p;

	cpt.j = 0;
	tmp = polygone;
	if (!tmp)
		return (cpt.j);
	cpt.x = tmp->x;
	cpt.i = 1;
	while (cpt.i < len)
	{
		p = get_point_in_list(tmp, cpt.i);
		if (p.x <= cpt.x)
		{
			cpt.x = p.x;
			cpt.j = cpt.i;
		}
		cpt.i++;
	}
	return (cpt.j);
}

int		is_in_triangle(t_count cpt, t_dot m, int distance, t_point p)
{
	cpt.x = fabs(pointside2(m, p.p1, p.p2.x, p.p2.y));
	if (cpt.x > distance)
	{
		distance = cpt.x;
		cpt.j = cpt.i;
	}
	return (cpt.j);
}

int		vertex_max_dist(t_lst *polygone, t_point p, int *tab)
{
	t_count	cpt;
	t_dot	m;
	int		distance;

	cpt.n = len_list(polygone);
	distance = 0;
	cpt.j = 0;
	cpt.i = 0;
	while (cpt.i < cpt.n)
	{
		if (cpt.i != tab[0] && cpt.i != tab[1] && cpt.i != tab[2])
		{
			m = get_point_in_list(polygone, cpt.i);
			if (point_in_triangle(p.p0, p.p1, p.p2, m) == 1)
				cpt.j = is_in_triangle(cpt, m, distance, p);
		}
		cpt.i++;
	}
	return (cpt.j);
	// free tab a la fin
}
