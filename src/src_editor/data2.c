/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:58:10 by abechet           #+#    #+#             */
/*   Updated: 2019/07/21 17:06:47 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_player_start(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = -1;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
		{
			ret = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
		ret = triangulate_player_start(win, tmp->x, tmp->y);
	return (ret);
}

int correct_intersections_in_a_sector(t_win *win)
{
	t_lstlst	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lst		*tmp0;
	t_dot		p1;
	t_dot		p2;
	t_dot		p3;
	t_dot		p4;
	int			ret;
	int			index3;
	int			index2;
	int			len;
	int			index4;
	int			index5;

	index3 = 0;
	ret = -1;
	tmp3 = win->lstlst;
	while (tmp3)
	{
		tmp = tmp3->head;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				p2.x = tmp3->head->next->x;
				p2.y = tmp3->head->next->y;
			}
			else
			{
				p2.x = tmp->next->x;
				p2.y = tmp->next->y;
			}
			p1.x = tmp->x;
			p1.y = tmp->y;
			tmp2 = win->lstlst;
			index2 = 0;
			while (tmp2)
			{
				tmp0 = tmp2->head;
				len = len_list(tmp0);
				index4 = index3 + len - 2;
				index5 = index2 + len - 2;
				while (tmp0)
				{
					if (index2 != index3 && index3 + 1 != index2
						&& index4 != index2 && index4 + 1 != index2)
					{
						if (index3 != index2 && index2 + 1 != index3
							&& index5 != index3 && index5 + 1 != index3)
						{
							if (tmp0->next == NULL)
							{
								p4.x = tmp2->head->next->x;
								p4.y = tmp2->head->next->y;
							}
							else
							{
								p4.x = tmp0->next->x;
								p4.y = tmp0->next->y;
							}
							p3.x = tmp0->x;
							p3.y = tmp0->y;
							if ((ret = sector_intersect_with_itself(p1,
								p2, p3, p4)) == 1)
							{

								if ((p1.x != p2.x || p1.y != p2.y) && (p2.x != p3.x || p2.y != p3.y) && (p3.x != p4.x || p3.y != p4.y)
								&& (p4.x != p1.x || p4.y != p1.y))
								{
									if (tmp->sector != tmp0->sector)
									{
										 if ((p1.x != p3.x || p1.y != p3.y) && (p2.x != p4.x || p2.y != p4.y))
										 {
											printf("Crossed segments \n");
		 									return (-3);
										}
									}
									else
									{
										printf("Crossed segments \n");
										return (-3);
									}

								}
							}
						}
					}
					index2++;
					tmp0 = tmp0->next;
				}
				tmp2 = tmp2->next;
			}
			index3++;
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	return (0);
}

int		point_in_triangle2(t_dot p0, t_dot p1, t_dot p2, t_dot m)
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

int			sector_inside_sector(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*tmp3;
	t_lst		*tmp;
	t_lst		*tmp0;
	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	t_dot		m;
	int			ret;

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
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			point_on_top(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			index;
	int			index0;


	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		index = 0;
		while (tmp->next)
		{
			index0 = 0;
			tmp0 = tmp2->head;
			while (tmp0->next)
			{
				if (index != index0)
				{
					if (tmp->x == tmp0->x && tmp->y == tmp0->y)
						return (-6);
				}
				tmp0 = tmp0->next;
				index0++;
			}
			tmp = tmp->next;
			index++;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

/*int			sectors_on_top(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*tmp3;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			len;
	int			i;

	tmp2 = win->lstlst;
	while (tmp2->next)
	{
		tmp3 = tmp2->next;
		while (tmp3)
		{
			i = 0;
			tmp = tmp2->head;
			tmp0 = tmp3->head;
			while (tmp && tmp0)
			{
				if (tmp->x == tmp0->x && tmp->y == tmp0->y)
					i++;
				tmp = tmp->next;
				tmp0 = tmp0->next;
			}
			len = len_list(tmp2->head);
			if (i == len)
				return (-7);
			tmp3 = tmp3->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}*/

int			sectors_on_top(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*tmp3;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			len2;
	int			i;

	tmp2 = win->lstlst;
	while (tmp2->next)
	{
		tmp3 = tmp2->next;
		len2 = len_list(tmp2->head);
		while (tmp3)
		{
			if (len2 == len_list(tmp3->head))
			{
				i = 0;
				tmp = tmp2->head;
				while (tmp->next)
				{
					tmp0 = tmp3->head;
					while (tmp0->next)
					{
						if (tmp->x == tmp0->x && tmp->y == tmp0->y)
							i++;
						tmp0 = tmp0->next;
					}
					tmp = tmp->next;
				}
				if (i == len2 - 1)
					return (-7);
			}
			tmp3 = tmp3->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_map(t_win *win)
{
	int			ret;

	ret = 0;
	ret = sectors_on_top(win);
	if (ret == -7)
	{
		printf("Two sectors on top of each other\n");
		return (ret);
	}
	ret = point_on_top(win);
	if (ret == -6)
	{
		printf("Two points on top of each other in same sector\n");
		return (ret);
	}
	ret = sector_inside_sector(win);
	if (ret == -5)
	{
		printf("Sector inside a sector\n");
		return (ret);
	}
	ret = correct_three_points(win);
	if (ret == -4)
	{
		printf("Too many points of a sector on same x\n");
		return (ret);
	}
	ret = correct_intersections_in_a_sector(win);
	if (ret == -3)
	{
		printf("Crossed segments \n");
		return (ret);
	}
	ret = check_player_start(win);
	if (ret == -1)
		printf("Map need a player start \n");
	if (ret == -2)
		printf("Player start need to be inside a sector \n");
	return (ret);
}
