/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:59:43 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:18:58 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			number_of_points_in_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			j;
	int			index;
	int			nb;
	int			*dot_tab;

	dot_tab = NULL;
	index = 0;
	i = 0;
	j = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			i = len_list(tmp);
			dot_tab = dot_tab_sector(win, sector);
			nb = dot_tab[index];
			j++;
			while (index < i)
			{
				if (dot_tab[index] > nb)
				{
					j++;
					nb = dot_tab[index];
				}
				index++;
			}
			break ;
		}
		free_dot_tab(dot_tab);
		tmp2 = tmp2->next;
	}
	return (j);
}

int			number_of_ennemy(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int			number_of_sprite(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
