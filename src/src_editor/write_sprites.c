/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data17.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:27:19 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 19:56:23 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			correct_three_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		i = 0;
		tmp = tmp2->head;
		while (tmp->next)
		{
			if (tmp->x == tmp->next->x)
				i++;
			else
				i = 0;
			if (i > 1)
				return (-4);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

void		write_sprites_helper(t_win *win, int fp, t_lstast *tmp, int i)
{
	if (tmp->asset_type == 1)
		write_m4(win, fp, tmp, i);
	if (tmp->asset_type == 2)
		write_shotgun(win, fp, tmp, i);
	if (tmp->asset_type == 4)
		write_m4_ammo(win, fp, tmp, i);
	if (tmp->asset_type == 5)
		write_m9(win, fp, tmp, i);
	if (tmp->asset_type == 6)
		write_health(win, fp, tmp, i);
	if (tmp->asset_type == 7)
		write_shotgun_ammo(win, fp, tmp, i);
	if (tmp->asset_type == 8)
		write_undertale(win, fp, tmp, i);
}

void		write_sprites(t_win *win, int fp)
{
	t_lstast	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstast;
	str = "Section:sprite\n";
	ft_putstr_fd(str, fp);
	while (tmp)
	{
		write_sprites_helper(win, fp, tmp, i);
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
		{
			i++;
			str = "\n";
			ft_putstr_fd(str, fp);
		}
		tmp = tmp->next;
	}
}
