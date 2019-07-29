/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:50:58 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:51:10 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_sectors_neighbours(t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;
	int			i;
	int			len;

	i = 0;
	len = len_list(tmp2->head);
	while (i < len)
	{
		if (triangles_neighbours(win, tmp2, i) == -1)
		{
			str = "x";
			ft_putstr_fd(str, fp);
		}
		else
		{
			str = ft_itoa(triangles_neighbours(win, tmp2, i));
			ft_putstr_fd(str, fp);
		}
		if (i < len - 1)
		{
			str = ",";
			ft_putstr_fd(str, fp);
		}
		i++;
	}
}

void		write_sectors_textures(int fp, t_lstlst *tmp2)
{
	char		*str;

	str = ":";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp2->txtr_floor);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp2->txtr_ceiling);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp2->txtr_wall);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp2->txtr_lower_extrude);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp2->txtr_higher_extrude);
	ft_putstr_fd(str, fp);
	str = ",2";
	ft_putstr_fd(str, fp);
}

void		write_sectors_helper2(t_win *win, int fp, t_lstlst *tmp2)
{
	char	*str;
	t_lst	*tmp;

	tmp = tmp2->head;
	if (tmp2->clockwise == 2)
	{
		str = ft_itoa(tmp->nb);
		ft_putstr_fd(str, fp);
		str = ",";
		ft_putstr_fd(str, fp);
		str = ft_itoa(tmp->next->next->nb);
		ft_putstr_fd(str, fp);
		str = ",";
		ft_putstr_fd(str, fp);
		str = ft_itoa(tmp->next->nb);
		ft_putstr_fd(str, fp);
	}
	str = ":";
	ft_putstr_fd(str, fp);
	write_sectors_neighbours(win, fp, tmp2);
	write_sectors_textures(fp, tmp2);
	str = "\n";
	ft_putstr_fd(str, fp);
}

void		write_sectors_helper(t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;
	t_lst		*tmp;

	str = "\tsector:0,30:";
	ft_putstr_fd(str, fp);
	tmp = tmp2->head;
	if (tmp2->clockwise == 1)
	{
		while (tmp)
		{
			str = ft_itoa(tmp->nb);
			ft_putstr_fd(str, fp);
			tmp = tmp->next;
			if (tmp)
			{
				str = ",";
				ft_putstr_fd(str, fp);
			}
		}
	}
	write_sectors_helper2(win, fp, tmp2);
}

void		write_sectors(t_win *win, int fp)
{
	int			i;
	int			index;
	t_lstlst	*tmp2;

	index = 0;
	i = len_listlist(win->triangles);
	tmp2 = win->triangles;
	while (index < i)
	{
		if (tmp2->sector != -1)
			write_sectors_helper(win, fp, tmp2);
		index++;
		tmp2 = tmp2->next;
	}
}
