/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:04:46 by abechet           #+#    #+#             */
/*   Updated: 2019/07/24 12:04:56 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_dot		first_dot(t_lst *tmp, t_lstlst *tmp2, t_dot p2)
{
	if (tmp->next == NULL)
	{
		p2.x = tmp2->head->next->x;
		p2.y = tmp2->head->next->y;
	}
	else
	{
		p2.x = tmp->next->x;
		p2.y = tmp->next->y;
	}
	return (p2);
}

int			is_crossed(t_point p, t_lst *tmp, t_lst *tmp0)
{
	if ((p.p1.x != p.p2.x || p.p1.y != p.p2.y)
		&& (p.p2.x != p.p3.x || p.p2.y != p.p3.y)
			&& (p.p3.x != p.p4.x || p.p3.y != p.p4.y)
				&& (p.p4.x != p.p1.x || p.p4.y != p.p1.y))
	{
		if (tmp->sector != tmp0->sector)
		{
			if ((p.p1.x != p.p3.x || p.p1.y != p.p3.y)
				&& (p.p2.x != p.p4.x || p.p2.y != p.p4.y))
			{
				ft_putendl("Crossed segments");
				return (-3);
			}
		}
		else
		{
			ft_putendl("Crossed segments");
			return (-3);
		}
	}
	return (0);
}

int			one_sector(t_point p, t_lst *tmp, t_lst *tmp0, t_lstlst *tmp2)
{
	while (tmp0)
	{
		if (p.index2 != p.index3 && p.index3 + 1 != p.index2
			&& p.index4 != p.index2 && p.index4 + 1 != p.index2)
		{
			if (p.index3 != p.index2 && p.index2 + 1 != p.index3
				&& p.index5 != p.index3 && p.index5 + 1 != p.index3)
			{
				p.p4 = first_dot(tmp0, tmp2, p.p4);
				p.p3.x = tmp0->x;
				p.p3.y = tmp0->y;
				if ((p.ret = sector_intersect_with_itself(p.p1,
					p.p2, p.p3, p.p4)) == 1)
					if (is_crossed(p, tmp, tmp0) == -3)
						return (-3);
			}
		}
		p.index2++;
		tmp0 = tmp0->next;
	}
	return (0);
}

int			multi_sector(t_lstlst *tmp2, t_lst *tmp, t_point p)
{
	t_lst		*tmp0;

	p.index2 = 0;
	while (tmp2)
	{
		tmp0 = tmp2->head;
		p.len = len_list(tmp0);
		p.index4 = p.index3 + p.len - 2;
		p.index5 = p.index2 + p.len - 2;
		if (one_sector(p, tmp, tmp0, tmp2) == -3)
			return (-3);
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_intersections_in_a_sector(t_win *win)
{
	t_lstlst	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_point		p;

	p.index3 = 0;
	tmp3 = win->lstlst;
	while (tmp3)
	{
		tmp = tmp3->head;
		while (tmp)
		{
			p.p2 = first_dot(tmp, tmp3, p.p2);
			p.p1.x = tmp->x;
			p.p1.y = tmp->y;
			tmp2 = win->lstlst;
			if (multi_sector(tmp2, tmp, p) == -3)
				return (-3);
			p.index3++;
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	return (0);
}
