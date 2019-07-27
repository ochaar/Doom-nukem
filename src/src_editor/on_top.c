/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_top.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:02:29 by abechet           #+#    #+#             */
/*   Updated: 2019/07/24 12:02:39 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_player_start(t_win *win)
{
	t_lstast	*tmp;
	int			ret;

	ret = -1;
	tmp = win->lstast;
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

int			point_on_top_helper(t_lstlst *tmp2, t_lst *tmp, t_lst *tmp0)
{
	int			index;
	int			index0;

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
					if (tmp->x == tmp0->x && tmp->y == tmp0->y)
						return (-6);
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

int			point_on_top(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			ret;

	tmp = NULL;
	tmp0 = NULL;
	tmp2 = win->lstlst;
	ret = point_on_top_helper(tmp2, tmp, tmp0);
	if (ret == -6)
		return (-6);
	return (0);
}

int			sectors_on_top_helper(t_lst *tmp, t_lstlst *tmp3)
{
	int		i;
	t_lst	*tmp0;

	i = 0;
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
	return (i);
}

int			sectors_on_top(t_lstlst *tmp2)
{
	t_lstlst	*tmp3;
	t_lst		*tmp;
	int			len2;
	int			i;

	while (tmp2->next)
	{
		tmp3 = tmp2->next;
		len2 = len_list(tmp2->head);
		while (tmp3)
		{
			if (len2 == len_list(tmp3->head))
			{
				tmp = tmp2->head;
				i = sectors_on_top_helper(tmp, tmp3);
				if (i == len2 - 1)
					return (-7);
			}
			tmp3 = tmp3->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}
