/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:28:55 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 17:29:07 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fl2_helper(t_win *win, int fp, int i)
{
	char		*str;

	str = ",sector:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",sprite:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(number_of_sprite(win), win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",ennemy:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(number_of_ennemy(win), win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "Section:map\n";
	ft_putstr_fd(str, fp);
}

void		first_line2(t_env *w, t_win *win, int fp)
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
	ft_light_itoa(total_exclusive_points(w, win), win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	fl2_helper(win, fp, i);
}
