/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:49:04 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:49:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_player_helper(t_win *win, int fp, t_lstasset *tmp, char *str)
{
	str = "\tplayer_sector:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tplayer_max_hp:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(win->hp_value);
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tgravity:0.0";
	ft_putstr_fd(str, fp);
	str = ft_itoa(win->gravity_value);
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tgod_mod:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(win->god_value);
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
}

void		write_player(t_win *win, int fp)
{
	char		*str;
	t_lstasset	*tmp;

	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			break ;
		tmp = tmp->next;
	}
	str = "Section:player\n";
	ft_putstr_fd(str, fp);
	str = "\tplayer_location:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tplayer_direction:90\n";
	ft_putstr_fd(str, fp);
	write_player_helper(win, fp, tmp, str);
}

void		write_m4(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tM4A1:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",0,";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_shotgun(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tpompe:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",1,";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}
