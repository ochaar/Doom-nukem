/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:45:55 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:46:05 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_shotgun_ammo(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\tcartouche:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",4,";
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

void		write_m4_ammo(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\tammo:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",5,";
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

void		write_m9(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\tM9:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",2,";
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

void		write_health(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\thealth:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",3,";
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

void		write_undertale(t_win *win, int fp, t_lstast *tmp, int i)
{
	char		*str;

	if (win->lstast)
	{
		str = "\tundertale:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",14,";
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
