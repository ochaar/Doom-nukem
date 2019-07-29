/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data16.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:09:00 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 16:41:47 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fill_buffer(t_win *win, t_env *w)
{
	win->number = 0;
	sort_points(win);
	write_in_file(win, w);
}

int			tpsh(t_lstlst *tmp2, t_dot m)
{
	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	int			ret;

	ret = -2;
	p0 = get_point_in_list(tmp2->head, 0);
	p1 = get_point_in_list(tmp2->head, 1);
	p2 = get_point_in_list(tmp2->head, 2);
	ret = point_in_triangle(p0, p1, p2, m);
	if (ret == 1)
	{
		ret = 0;
		return (ret);
	}
	else
		ret = -2;
	return (ret);
}

int			triangulate_player_start(t_win *win, int x, int y)
{
	t_lstlst	*tmp2;
	int			ret;
	t_dot		m;

	m.x = x;
	m.y = y;
	ret = -2;
	tmp2 = win->triangles;
	ret = triangulate_a_triangle(win, m);
	if (ret != -1)
		return (0);
	while (tmp2)
	{
		ret = tpsh(tmp2, m);
		if (ret == 0)
			return (ret);
		tmp2 = tmp2->next;
	}
	return (ret);
}

int			sector_intersect_with_itself(t_dot p1, t_dot p2, t_dot p3, t_dot p4)
{
	int	i1;
	int	i2;
	int	i3;
	int	i4;

	i1 = pointside2(p3, p1, p2.x, p2.y);
	i2 = pointside2(p4, p1, p2.x, p2.y);
	i3 = pointside2(p1, p3, p4.x, p4.y);
	i4 = pointside2(p2, p3, p4.x, p4.y);
	if (i1 == 0 && i2 == 0 && i3 == 0 && i4 == 0)
		return (0);
	else if (i1 >= 0 && i2 <= 0 && i3 >= 0 && i4 <= 0)
		return (1);
	else if (i1 <= 0 && i2 >= 0 && i3 <= 0 && i4 >= 0)
		return (1);
	else if (i1 <= 0 && i2 >= 0 && i3 >= 0 && i4 <= 0)
		return (1);
	else if (i1 >= 0 && i2 <= 0 && i3 <= 0 && i4 >= 0)
		return (1);
	return (0);
}

int			sector_minimum_needed_point(t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (len_list(tmp2->head) <= 3)
			return (-4);
		tmp2 = tmp2->next;
	}
	return (0);
}
