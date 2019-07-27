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

void		write_sectors_neighbours(t_env *w,
				t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;
	int			len;

	win->tni = 0;
	len = len_list(tmp2->head);
	while (win->tni < len)
	{
		if (triangles_neighbours(w, win, tmp2) == -1)
		{
			str = "x";
			ft_putstr_fd(str, fp);
		}
		else
		{
			ft_light_itoa(triangles_neighbours(w, win, tmp2), win->itoastr);
			ft_putstr_fd(win->itoastr, fp);
		}
		if (win->tni < len - 1)
		{
			str = ",";
			ft_putstr_fd(str, fp);
		}
		win->tni++;
	}
}

void		write_sectors_textures(t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;

	str = ":";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp2->txtr_floor, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp2->txtr_ceiling, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp2->txtr_wall, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp2->txtr_lower_extrude, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp2->txtr_higher_extrude, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",48";
	ft_putstr_fd(str, fp);
}

void		write_sectors_helper2(t_env *w, t_win *win, int fp, t_lstlst *tmp2)
{
	char	*str;
	t_lst	*tmp;

	tmp = tmp2->head;
	if (tmp2->clockwise == 2)
	{
		ft_light_itoa(tmp->nb, win->itoastr);
		ft_putstr_fd(win->itoastr, fp);
		str = ",";
		ft_putstr_fd(str, fp);
		ft_light_itoa(tmp->next->next->nb, win->itoastr);
		ft_putstr_fd(win->itoastr, fp);
		str = ",";
		ft_putstr_fd(str, fp);
		ft_light_itoa(tmp->next->nb, win->itoastr);
		ft_putstr_fd(win->itoastr, fp);
	}
	str = ":";
	ft_putstr_fd(str, fp);
	write_sectors_neighbours(w, win, fp, tmp2);
	write_sectors_textures(win, fp, tmp2);
	str = "\n";
	ft_putstr_fd(str, fp);
}

void		write_sectors_helper(t_env *w, t_win *win, int fp, t_lstlst *tmp2)
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
			ft_light_itoa(tmp->nb, win->itoastr);
			ft_putstr_fd(win->itoastr, fp);
			tmp = tmp->next;
			if (tmp)
			{
				str = ",";
				ft_putstr_fd(str, fp);
			}
		}
	}
	write_sectors_helper2(w, win, fp, tmp2);
}

void		write_sectors(t_env *w, t_win *win, int fp)
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
			write_sectors_helper(w, win, fp, tmp2);
		index++;
		tmp2 = tmp2->next;
	}
}
