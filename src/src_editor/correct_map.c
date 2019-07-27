/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:58:10 by abechet           #+#    #+#             */
/*   Updated: 2019/07/24 10:52:19 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			point_in_triangle2(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (pointside2(m, p0, p1.x, p1.y) >= 0)
	{
		if (pointside2(m, p0, p1.x, p1.y) > 0
		&& pointside2(m, p1, p2.x, p2.y) > 0
		&& pointside2(m, p2, p0.x, p0.y) > 0)
			return (1);
	}
	else
	{
		if (pointside2(m, p0, p1.x, p1.y) < 0
		&& pointside2(m, p1, p2.x, p2.y) < 0
		&& pointside2(m, p2, p0.x, p0.y) < 0)
			return (1);
	}
	return (0);
}

int			sector_inside_sector_helper(t_dot m, t_lstlst *tmp3, t_lstlst *tmp2)
{
	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	int			ret;
	t_lst		*tmp0;

	ret = 0;
	while (tmp3)
	{
		if (tmp3->sector != -1)
		{
			tmp0 = tmp3->head;
			if (tmp3->sector != tmp2->sector)
			{
				p0 = get_point_in_list(tmp0, 0);
				p1 = get_point_in_list(tmp0, 1);
				p2 = get_point_in_list(tmp0, 2);
				ret = point_in_triangle2(p0, p1, p2, m);
				if (ret == 1)
					return (-5);
			}
		}
		tmp3 = tmp3->next;
	}
	return (0);
}

int			sector_inside_sector(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*tmp3;
	t_lst		*tmp;
	t_dot		m;

	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector != -1)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				tmp3 = win->triangles;
				m.x = tmp->x;
				m.y = tmp->y;
				if (sector_inside_sector_helper(m, tmp3, tmp2) == -5)
					return (-5);
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_map_helper(t_win *win)
{
	t_lstlst	*tmp2;
	int			ret;

	tmp2 = win->lstlst;
	ret = 0;
	ret = sectors_on_top(tmp2);
	if (ret == -7)
	{
		ft_putendl("Two sectors on top of each other");
		return (ret);
	}
	ret = point_on_top(win);
	if (ret == -6)
	{
		ft_putendl("Two points on top of each other in same sector");
		return (ret);
	}
	ret = sector_inside_sector(win);
	if (ret == -5)
	{
		ft_putendl("Sector inside a sector");
		return (ret);
	}
	return (ret);
}

int			correct_map(t_win *win)
{
	int		ret;

	ret = 0;
	ret = correct_map_helper(win);
	if (ret != 0)
		return (ret);
	ret = correct_three_points(win);
	if (ret == -4)
	{
		ft_putendl("Too many points of a sector on same x");
		return (ret);
	}
	ret = correct_intersections_in_a_sector(win);
	if (ret == -3)
	{
		ft_putendl("Crossed segments");
		return (ret);
	}
	ret = check_player_start(win);
	if (ret == -1)
		ft_putendl("Map need a player start");
	if (ret == -2)
		ft_putendl("Player start need to be inside a sector");
	return (ret);
}
