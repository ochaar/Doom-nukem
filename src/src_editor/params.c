/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:34:38 by abechet           #+#    #+#             */
/*   Updated: 2019/07/11 12:37:42 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		increase_value(t_win *win)
{
	if (win->param_index == 0)
	{
		if (win->hp_value < 1000)
			win->hp_value += 10;
	}
	if (win->param_index == 1)
	{
		if (win->gravity_value < 9)
			win->gravity_value++;
	}
	if (win->param_index == 2)
	{
		if (win->god_value < 1)
			win->god_value++;
	}
}

void		decrease_value(t_win *win)
{
	if (win->param_index == 0)
	{
		if (win->hp_value > 10)
			win->hp_value -= 10;
	}
	if (win->param_index == 1)
	{
		if (win->gravity_value > 0)
			win->gravity_value--;
	}
	if (win->param_index == 2)
	{
		if (win->god_value > 0)
			win->god_value--;
	}
}

void		param_text(t_win *win)
{
	char	*tmp;

	if (win->param_index == 0)
	{
		win->paramtxt = ft_strdup("HP");
		tmp = ft_itoa(win->hp_value);
		win->paramvaluetxt = ft_strdup(tmp);
	}
	if (win->param_index == 1)
	{
		win->paramtxt = ft_strdup("Gravity");
		tmp = ft_itoa(win->gravity_value);
		win->paramvaluetxt = ft_strdup(tmp);
	}
	if (win->param_index == 2)
	{
		win->paramtxt = ft_strdup("God Mode");
		if (win->god_value)
			win->paramvaluetxt = ft_strdup("ON");
		else
			win->paramvaluetxt = ft_strdup("OFF");
	}
}

void		set_params(t_env *w, t_win *win)
{
	param_text(win);
	win->dst12.x = win->x2 + 30;
	win->dst12.y = win->y2 - 20;
	win->dst13.x = win->x2 + 30;
	win->dst13.y = win->y2 + 20;
	type_str(w, win->dst12, win->paramtxt, 0xFF00FF);
	type_str(w, win->dst13, win->paramvaluetxt, 0xFF00FF);
}
