/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:44:59 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 16:03:14 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	affichage_set(t_env *w)
{
	t_dot	dot;

	affichage_set_str(w);
	dot.x = WIDTH - 100;
	dot.y = 110;
	ft_light_itoa(w->fov_h_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->fov_v_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->mousesp_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.x = w->txthead.x;
	dot.y = w->txthead.y;
}

void	change_key(t_env *w)
{
	char *tmp;

	if (w->menu.k == 5)
	{
		w->window_mode = 1;
		w->window_res = 0;
		w->m->player.field_of_vision_h = 512;
		w->m->player.field_of_vision_v = 288;
		w->m->player.mousesp = 100;
	}
	else
	{
		w->window_mode = w->window_mode_menu;
		w->window_res = w->window_res_menu;
		w->m->player.field_of_vision_h = w->fov_h_menu;
		w->m->player.field_of_vision_v = w->fov_v_menu;
		w->m->player.mousesp = w->mousesp_menu;
	}
	if ((tmp = ft_itoa(w->window_res)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "settings_changed"));
	change_settings(w, w->m);
	set_screen_res(w, tmp);
	fit_to_game(w);
	free(tmp);
}

void	event_menu_settings(t_env *w)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == SDLK_ESCAPE)
				w->menu.i = vmax(-1, w->menu.i - 2);
			if (KEY == SDLK_RETURN && w->menu.k > 4)
			{
				if (settings_changed(w) == 1)
					change_key(w);
				w->menu.i = 1;
			}
			if (KEY == SDLK_UP)
				w->menu.k = ((w->menu.k - 1) < 0) ? 6 : (w->menu.k - 1);
			if (KEY == SDLK_DOWN)
				w->menu.k = ((w->menu.k + 1) > 6) ? 0 : (w->menu.k + 1);
			if (KEY == SDLK_RIGHT)
				change_value_settings(w, 1);
			if (KEY == SDLK_LEFT)
				change_value_settings(w, 2);
		}
		if (w->event.type == SDL_WINDOWEVENT)
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
	}
}

void	aff_settings(t_env *w)
{
	t_dot dot;

	dot = fill_t_dot(10, 10);
	type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
	dot = fill_t_dot(10, 10 + w->menu.k * 50);
	if (w->menu.k == 0)
		type_str(w, dot, "WINDOW MODE :\n", 0x12FEA800);
	else if (w->menu.k == 1)
		type_str(w, dot, "WINDOW RESOLUTION :\n", 0x12FEA800);
	else if (w->menu.k == 2)
		type_str(w, dot, "FOV HORIZONTAL :\n", 0x12FEA800);
	else if (w->menu.k == 3)
		type_str(w, dot, "FOV VERTICAL :\n", 0x12FEA800);
	else if (w->menu.k == 4)
		type_str(w, dot, "MOUSE SENSITIVITY :\n", 0x12FEA800);
	else if (w->menu.k == 5)
		type_str(w, dot, "RESET TO DEFAULT\n", 0x12FEA800);
	else
		type_str(w, dot, "SAVE\n", 0x12FEA800);
}

void	menu_settings(t_env *w)
{
	t_dot dot;

	w->menu.k = 0;
	w->window_mode_menu = w->window_mode;
	w->window_res_menu = w->window_res;
	w->fov_h_menu = w->m->player.field_of_vision_h;
	w->fov_v_menu = w->m->player.field_of_vision_v;
	w->mousesp_menu = w->m->player.mousesp;
	while (1)
	{
		main_pic(w, 1);
		aff_settings(w);
		dot = fill_t_dot(WIDTH - 480, HEIGHT - 40);
		type_str(w, dot, "PRESS ENTER TO SAVE AND APPLY", 0x12FEA800);
		event_menu_settings(w);
		affichage_set(w);
		if (w->menu.i != 3)
			break ;
		img_update(w);
	}
}
