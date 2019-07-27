/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:44:59 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 09:10:35 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	main_pic(t_env *w, int nb)
{
	t_img	img;

	if (nb < 0 || nb > 3)
		return ;
	img = fill_t_img(0, 0, WIDTH, HEIGHT);
	img_to_screen(w, w->main_pic[nb], img);
}

int		map_is_in_core(t_env *w, char *map)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	w->nbmaps = get_nb_maps_in_core(w);
	if ((w->namesmaps = (char **)malloc(sizeof(char *)
		* (w->nbmaps + 1))) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "map_is_in_core"));
	get_names_maps_in_core(w, w->m, w->namesmaps);
	w->namesmaps[w->nbmaps] = NULL;
	while (w->namesmaps[i])
	{
		if (ft_strcmp(w->namesmaps[i], map) == 0)
			found = 1;
		i++;
	}
	ft_memreg(w->namesmaps);
	if (found == 1)
		return (1);
	else
		return (0);
}

void	change_value_settings_nxt(t_env *w, int direction)
{
	if (w->menu.k == 3)
	{
		if (direction == 1)
			w->fov_v_menu = vmin(w->fov_v_menu + 1, 500);
		else
			w->fov_v_menu = vmax(100, w->fov_v_menu - 1);
	}
	else if (w->menu.k == 4)
	{
		if (direction == 1)
			w->mousesp_menu = vmin(w->mousesp_menu + 1, 200);
		else
			w->mousesp_menu = vmax(1, w->mousesp_menu - 1);
	}
}

void	change_value_settings(t_env *w, int direction)
{
	if (w->menu.k == 0)
	{
		if (direction == 1)
			w->window_mode_menu = vmin(w->window_mode_menu + 1, 1);
		else
			w->window_mode_menu = vmax(0, w->window_mode_menu - 1);
	}
	else if (w->menu.k == 1)
	{
		if (direction == 1)
			w->window_res_menu = vmin(w->window_res_menu + 1, 1);
		else
			w->window_res_menu = vmax(0, w->window_res_menu - 1);
	}
	else if (w->menu.k == 2)
	{
		if (direction == 1)
			w->fov_h_menu = vmin(w->fov_h_menu + 1, 700);
		else
			w->fov_h_menu = vmax(300, w->fov_h_menu - 1);
	}
	else if (w->menu.k >= 3)
		change_value_settings_nxt(w, direction);
}

int		settings_changed(t_env *w)
{
	if (w->menu.k == 5)
	{
		if (w->window_mode != 1 || w->window_res != 0)
			return (1);
		if (w->m->player.field_of_vision_h != 512)
			return (1);
		if (w->m->player.field_of_vision_v != 288)
			return (1);
		if (w->m->player.mousesp != 100)
			return (1);
	}
	else
	{
		if (w->window_mode != w->window_mode_menu)
			return (1);
		if (w->window_res != w->window_res_menu)
			return (1);
		if (w->m->player.field_of_vision_h != w->fov_h_menu)
			return (1);
		if (w->m->player.field_of_vision_v != w->fov_v_menu)
			return (1);
		if (w->m->player.mousesp != w->mousesp_menu)
			return (1);
	}
	return (0);
}
