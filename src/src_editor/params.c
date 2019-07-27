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

void		param_text_helper(t_env *w, t_win *win)
{
	if (win->param_index == 1)
	{
		if (win->paramtxt)
			free(win->paramtxt);
		win->paramtxt = strdup_safe(w, win, "Gravity");
		ft_light_itoa(win->gravity_value, win->itoastr);
		if (win->paramvaluetxt != NULL)
			free(win->paramvaluetxt);
		win->paramvaluetxt = strdup_safe(w, win, win->itoastr);
	}
	if (win->param_index == 2)
	{
		if (win->paramtxt)
			free(win->paramtxt);
		win->paramtxt = strdup_safe(w, win, "God Mode");
		if (win->paramvaluetxt != NULL)
			free(win->paramvaluetxt);
		if (win->god_value)
			win->paramvaluetxt = strdup_safe(w, win, "ON");
		else
			win->paramvaluetxt = strdup_safe(w, win, "OFF");
	}
}

void		param_text(t_env *w, t_win *win)
{
	if (win->param_index == 0)
	{
		if (win->paramtxt != NULL)
			free(win->paramtxt);
		win->paramtxt = strdup_safe(w, win, "HP");
		ft_light_itoa(win->hp_value, win->itoastr);
		if (win->paramvaluetxt != NULL)
			free(win->paramvaluetxt);
		win->paramvaluetxt = strdup_safe(w, win, win->itoastr);
	}
	param_text_helper(w, win);
}

void		set_params(t_env *w, t_win *win)
{
	param_text(w, win);
	win->dst12.x = win->x2 + 30;
	win->dst12.y = win->y2 - 20;
	win->dst13.x = win->x2 + 30;
	win->dst13.y = win->y2 + 20;
	type_str(w, win->dst12, win->paramtxt, 0xFF00FF);
	type_str(w, win->dst13, win->paramvaluetxt, 0xFF00FF);
}
