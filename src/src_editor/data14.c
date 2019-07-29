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

void		fl2_helper(t_win *win, int fp, int i)
{
	char		*str;

	str = ",sector:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",sprite:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(number_of_sprite(win));
	ft_putstr_fd(str, fp);
	str = ",ennemy:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(number_of_ennemy(win));
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "Section:map\n";
	ft_putstr_fd(str, fp);
}

void		first_line2(t_win *win, int fp)
{
	char		*str;
	t_lstlst	*tmp2;
	int			i;

	i = 0;
	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector != -1)
			i++;
		tmp2 = tmp2->next;
	}
	str = "dots:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(total_exclusive_points(win));
	ft_putstr_fd(str, fp);
	fl2_helper(win, fp, i);
}

/*void		write_dots_helper(t_win *win, int fp, int x, int y)
{
	char *str;

	str = "\tdots:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(y / 5);
	ft_putstr_fd(str, fp);
	str = ":";
	ft_putstr_fd(str, fp);
	x = x_min_on_line(win, y);
	str = ft_itoa(x / 5);
	ft_putstr_fd(str, fp);
}*/

void		write_dots(t_win *win, int fp)
{
	char		*str;
	int			i;
	int			x;
	int			y;
	int			index;
	int			boole;
	int			a;
	int			b;

	b = number_of_y(win);
	a = 0;
	boole = 0;
	y = y_min_point(win);
	while (a < b)
	{
		index = 1;
		if (boole == 0)
			boole = 1;
		else
			y = next_y(win, y);
		i = number_of_dot_per_line(win, y);
		str = "\tdots:";
		ft_putstr_fd(str, fp);
		str = ft_itoa(y / 5);
		ft_putstr_fd(str, fp);
		str = ":";
		ft_putstr_fd(str, fp);
		x = x_min_on_line(win, y);
		str = ft_itoa(x / 5);
		ft_putstr_fd(str, fp);
		while (index < i)
		{
			str = ",";
			ft_putstr_fd(str, fp);
			x = next_x_on_line(win, y, x);
			str = ft_itoa(x / 5);
			ft_putstr_fd(str, fp);
			index++;
		}
		str = "\n";
		ft_putstr_fd(str, fp);
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

int			*tab_sector3(t_win *win, int sector)
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
			clear_n_exit(win, 1);
		while (tmp)
		{
			dot_tab[index] = tmp->nb;
			index++;
			tmp = tmp->next;
		}
	}
	return (dot_tab);
}
