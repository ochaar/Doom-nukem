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

void		write_player_helper(t_win *win, int fp, t_lstast *tmp, char *str)
{
	str = "\tplayer_sector:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->sector, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tplayer_max_hp:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(win->hp_value, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tgravity:0.0";
	ft_putstr_fd(str, fp);
	ft_light_itoa(win->gravity_value, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tgod_mod:";
	ft_putstr_fd(str, fp);
	ft_light_itoa(win->god_value, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
}

void		write_player(t_win *win, int fp)
{
	char		*str;
	t_lstast	*tmp;

	tmp = win->lstast;
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
	ft_light_itoa(tmp->x / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->y / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "\tplayer_direction:90\n";
	ft_putstr_fd(str, fp);
	write_player_helper(win, fp, tmp, str);
}

void		write_m4(t_win *win, int fp, t_lstast *tmp, int i)
{
	char		*str;

	if (win->lstast)
	{
		str = "\tM4A1:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",0,";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->sector, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->x / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->y / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
}

void		write_shotgun(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\tpompe:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",1,";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->sector, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->x / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->y / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
}
