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

t_lst	*polylstnew(t_dot d)
{
	t_lst	*tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	tmp->x = d.x;
	tmp->y = d.y;
	tmp->next = NULL;
	return (tmp);
}

t_lst	*append_poly(t_lst *polygone, t_lst *p, t_lst **tmp, int i)
{
	if (p == NULL)
	{
		p = polylstnew(get_point_in_list(polygone, i));
		*tmp = p;
		if (p->x == -1 && p->y == -1)
			return (NULL);
	}
	else
	{
		while (p->next)
			p = p->next;
		p->next = polylstnew(get_point_in_list(polygone, i));
	}
	return (p);
}

t_lst	*new_poly(t_lst *polygone, int start, int end)
{
	int			n;
	int			i;
	t_lst		*p;
	t_lst		*tmp;

	p = NULL;
	tmp = NULL;
	n = len_list(polygone);
	i = start;
	while (i != end)
	{
		p = append_poly(polygone, p, &tmp, i);
		i = near_vertex(n, i, 1);
		if (i == -10000)
			return (p);
	}
	if (p)
	{
		while (p->next)
			p = p->next;
		p->next = polylstnew(get_point_in_list(polygone, i));
	}
	// free la liste quelque part
	return (tmp);
}
