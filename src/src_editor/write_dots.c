/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data14.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:00:45 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 14:00:55 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_dots_helper2(t_win *win, int y, int fp)
{
	char	*str;

	str = "\tdots:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(y / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ":";
	ft_putstr_fd(str, fp);
}

void		write_dots_helper(t_env *w, t_win *win, int fp, int y)
{
	char		*str;
	int			x;
	int			i;
	int			index;

	index = 1;
	i = number_of_dot_per_line(w, win, y);
	write_dots_helper2(win, y, fp);
	x = x_min_on_line(win, y);
	ft_light_itoa(x / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	while (index < i)
	{
		str = ",";
		ft_putstr_fd(str, fp);
		x = next_x_on_line(win, y, x);
		ft_light_itoa(x / 2, win->itoastr);
		ft_putstr_fd(win->itoastr, fp);
		index++;
	}
	str = "\n";
	ft_putstr_fd(str, fp);
}

void		write_dots(t_env *w, t_win *win, int fp, int boole)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;
	int			a;
	int			b;

	tmp2 = NULL;
	tmp = NULL;
	b = number_of_y(win, tmp2, tmp);
	a = 0;
	y = y_min_point(win);
	while (a < b)
	{
		if (boole == 0)
			boole = 1;
		else
			y = next_y(win, y);
		write_dots_helper(w, win, fp, y);
		a++;
	}
}

t_lstlst	*tab_sector3_helper(t_win *win, int sector)
{
	t_lstlst	*tmp2;

	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector == sector)
			break ;
		tmp2 = tmp2->next;
	}
	return (tmp2);
}

int			*tab_sector3(t_env *w, t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			i;
	int			index;

	dot_tab = NULL;
	i = 0;
	index = 0;
	tmp2 = tab_sector3_helper(win, sector);
	tmp = tmp2->head;
	i = len_list(tmp);
	if (tmp2)
	{
		if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
			clear_n_exit(w, win);
		while (tmp)
		{
			dot_tab[index] = tmp->nb;
			index++;
			tmp = tmp->next;
		}
	}
	return (dot_tab);
}
