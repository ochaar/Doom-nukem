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

void		write_shotgun_ammo(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tcartouche:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",4,";
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

void		write_m4_ammo(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tammo:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",5,";
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

void		write_m9(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tM9:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",2,";
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

void		write_health(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\thealth:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",3,";
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

void		write_undertale(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tundertale:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",14,";
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
