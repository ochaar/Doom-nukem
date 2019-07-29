/*BIG42HEADER*/

#include "doom.h"

void	main_pic(t_env *w, int nb)
{
	t_img	img;

	if (nb < 0 || nb > 3)
		return ;
	img = fill_t_img(0, 0, WIDTH, HEIGHT);
	img_to_screen(w, w->main_pic[nb], img);
}

void	menu_screen(t_env *w)
{
	t_dot	dot;
	char	*start;

	if (w->m->newgame == 1)
		if (w->menu.j == 1)
			start = ft_strdup("> NEW GAME\n");
		else
			start = ft_strdup("NEW GAME\n");
	else
		if (w->menu.j == 1)
			start = ft_strdup("> CONTINUE\n");
		else
			start = ft_strdup("CONTINUE\n");
	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	main_pic(w, 1);
	if (w->menu.j == 1)
	{
		type_str(w, dot, start, 0xFF78F7);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> MAPS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 3)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> SETTINGS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EDITOR\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EXIT", 0xFF78F7);
	}
	free(start);
}

void	affichage_set(t_env *w)
{
	t_dot	dot;

	dot.x = WIDTH - 100;
	dot.y = 10;
	ft_light_itoa(w->window_mode_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->window_res_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
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

void	change_value(t_env *w, int direction)
{
	if (w->menu.k == 0)
	{
		if (direction == 1)
			w->window_mode_menu = vmin(w->window_mode_menu + 1, 1);
		else
			w->window_mode_menu = vmax(0, w->window_mode_menu - 1);
	}
	if (w->menu.k == 1)
	{
		if (direction == 1)
			w->window_res_menu = vmin(w->window_res_menu + 1, 2);
		else
			w->window_res_menu = vmax(0, w->window_res_menu - 1);
	}
	if (w->menu.k == 2)
	{
		if (direction == 1)
			w->fov_h_menu = vmin(w->fov_h_menu + 1, 700);
		else
			w->fov_h_menu = vmax(300, w->fov_h_menu - 1);
	}
	if (w->menu.k == 3)
	{
		if (direction == 1)
			w->fov_v_menu = vmin(w->fov_v_menu + 1, 500);
		else
			w->fov_v_menu = vmax(100, w->fov_v_menu - 1);
	}
	if (w->menu.k == 4)
	{
		if (direction == 1)
			w->mousesp_menu = vmin(w->mousesp_menu + 1, 200);
		else
			w->mousesp_menu = vmax(1, w->mousesp_menu - 1);
	}
}

int		settings_changed(t_env *w)
{
	if (w->menu.k == 5)
	{
		if (w->window_mode != 1)
			return(1);
		if (w->window_res != 0)
			return(1);
		if (w->m->player.field_of_vision_h != 512)
			return(1);
		if (w->m->player.field_of_vision_v != 288)
			return(1);
		if (w->m->player.mousesp != 100)
			return(1);
	}
	else
	{
		if (w->window_mode != w->window_mode_menu)
			return(1);
		if (w->window_res != w->window_res_menu)
			return(1);
		if (w->m->player.field_of_vision_h != w->fov_h_menu)
			return(1);
		if (w->m->player.field_of_vision_v != w->fov_v_menu)
			return(1);
		if (w->m->player.mousesp != w->mousesp_menu)
			return(1);
	}
	return (0);
}

void	change_key(t_env *w)
{
	char *tmp;

	if (w->menu.k == 5 && settings_changed(w) == 1)
	{
		w->window_mode = 1;
		w->window_res = 0;
		w->m->player.field_of_vision_h = 512;
		w->m->player.field_of_vision_v = 288;
		w->m->player.mousesp = 100;
		change_settings(w, w->m);
	}
	else if (settings_changed(w) == 1)
	{
		w->window_mode = w->window_mode_menu;
		w->window_res = w->window_res_menu;
		w->m->player.field_of_vision_h = w->fov_h_menu;
		w->m->player.field_of_vision_v = w->fov_v_menu;
		w->m->player.mousesp = w->mousesp_menu;
		tmp = ft_itoa(w->window_res);
		set_screen_res(w, tmp);
		change_settings(w, w->m);
		free(tmp);
		fit_to_game(w);
	}
}

void	settings(t_env *w)
{
	t_dot	dot;

	w->menu.k = 0;
	w->window_mode_menu = w->window_mode;
	w->window_res_menu = w->window_res;
	w->fov_h_menu = w->m->player.field_of_vision_h;
	w->fov_v_menu = w->m->player.field_of_vision_v;
	w->mousesp_menu = w->m->player.mousesp;
	while (1)
	{
		main_pic(w, 1);
		dot.x = 10;
		dot.y = 10;
		if (w->menu.k == 0)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 1)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 2)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 3)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 4)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 5)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "SAVE\n", 0xFFFFFFFF);
		}
		else
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "SAVE\n", 0x12FEA800);
		}
		dot.x = WIDTH - 580;
		dot.y = HEIGHT - 55;
		type_str(w, dot, "PRESS ENTER TO SAVE AND APPLY", 0x12FEA800);
		type_str(w, w->txtnxtline, "PLEASE RESTART FOR WINDOW MODE AND RES", 0x12FEA800);
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 2);
				if (KEY == SDLK_RETURN && w->menu.k > 4)
				{
					change_key(w);
					w->menu.i = 1;
					break;
				}
				if (KEY == SDLK_UP)
					w->menu.k = ((w->menu.k - 1) < 0) ? 6 : (w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = ((w->menu.k + 1) > 6) ? 0 : (w->menu.k + 1);
				if (KEY == SDLK_RIGHT)
					change_value(w, 1);
				if (KEY == SDLK_LEFT)
					change_value(w, 2);
			}
			if (w->event.type == SDL_WINDOWEVENT)
			{
				if (WINDOW == SDL_WINDOWEVENT_CLOSE)
					exit_game(w, w->m, 1);
			}
		}
		affichage_set(w);
		if (w->menu.i != 3)
			break;
		img_update(w);
	} 
}

void	menu_maps_2(t_env *w)
{
	t_dot			dot;
	int 			i;
	int 			j;
	int 			start;
	unsigned int 	color;

	j = 0;
	start = 1;
	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	i = w->menu.k - 5;
	if (i < 0)
		i = w->nbmaps + i;
	while (j < 10)
	{
		if (i >= w->nbmaps)
			i = 0;
		if (i == w->menu.k)
			color = 0xFF78F7;
		else
			color = 0x12FEA800;
		if (start == 1)
			type_str(w, dot, w->namesmaps[i], color);
		else
			type_str(w, w->txtnxtline, w->namesmaps[i], color);
		start = 0;
		i++;
		j++;
	}
}

void	menu_maps_1(t_env *w)
{
	t_dot			dot;
	unsigned int 	color;
	int i;

	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	i = 0;
	while (w->namesmaps[i])
	{
		if (i == w->menu.k)
			color = 0xFF78F7;
		else
			color = 0x12FEA800;
		if (i == 0)
			type_str(w, dot, w->namesmaps[i], color);
		else
			type_str(w, w->txtnxtline, w->namesmaps[i], color);
		i++;
	}
}

void	maps(t_env *w)
{
	t_dot	dot;
	int		i;

	i = 0;
	w->menu.k = 0;
	dot.x = 10;
	dot.y = 10;
	w->nbmaps = get_nb_maps_in_core(w);
	if ((w->namesmaps = (char **)malloc(sizeof(char *) * (w->nbmaps + 1))) == NULL)
		set_error(w, w->m, 0, ft_strdup("menu_maps"));
	get_names_maps_in_core(w, w->namesmaps);
	w->namesmaps[w->nbmaps] = NULL;
	while (1)
	{
		dot.x = 10;
		dot.y = 10;
		main_pic(w, 1);
		type_str(w, dot, "MAPS :\n", 0xFFFFFFFF);
		if (w->nbmaps > 0 && w->nbmaps <= 10)
			menu_maps_1(w);
		else if (w->nbmaps > 10)
			menu_maps_2(w);
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 1);
				if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
				{
					free(w->currmap);
					w->currmap = ft_strdup(w->namesmaps[w->menu.k]);
					w->m->newgame = 1;
					w->menu.i = 5;
				}
				if (KEY == SDLK_UP)
					w->menu.k = ((w->menu.k - 1) < 0) ? w->nbmaps - 1 : (w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = ((w->menu.k + 1) >= w->nbmaps) ? 0 : (w->menu.k + 1);
			}
			if (w->event.type == SDL_WINDOWEVENT)
			{
				if (WINDOW == SDL_WINDOWEVENT_CLOSE)
					exit_game(w, w->m, 1);
			}
		}
		if (w->menu.i != 2)
		{
			i = 0;
			while (w->namesmaps[i])
			{
				free(w->namesmaps[i]);
				i++;
			}
			free(w->namesmaps);
			break;
		}
		img_update(w);
	}
}

void	event_menu(t_env *w)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == SDLK_ESCAPE)
			{
				w->menu.i = vmax(-1, w->menu.i - 1);
				w->m->newgame = 1;
			}
			if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
			{
				if (w->menu.j == 5)
					w->menu.i = -1;
				else if (w->menu.j == 4)
					w->menu.i = 4;
				else if (w->menu.j == 3)
					w->menu.i = 3;
				else if (w->menu.j == 2)
					w->menu.i = 2;
				else if (w->menu.j == 1)
					w->menu.i = 5;
				else
				{
					w->menu.j = 1;
					w->menu.i = vmin(w->menu.i + 1, 2);
				}
			}
			if (KEY == SDLK_UP)
				w->menu.j = ((w->menu.j - 1) < 1) ? 5 : (w->menu.j - 1);
			if (KEY == SDLK_DOWN)
				w->menu.j = ((w->menu.j + 1) > 5) ? 1 : (w->menu.j + 1);
		}
		if (w->event.type == SDL_WINDOWEVENT)
		{
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
		}
	}
}

void	main_menu(t_env *w, t_map *m)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_ENABLE);
	Mix_PauseMusic();
	w->txthead.x = 800;
	w->txthead.y = 550;
	w->menu.j = 1;
	while (1)
	{
		event_menu(w);
		if (w->menu.i == -1)
			exit_game(w, m, 1);
		if (w->menu.i == 0)
		{
			main_pic(w, 0);
			type_str(w, w->txthead, "press enter...", 0x12FEA800);
			w->menu.j = -1;
		}
		else if (w->menu.i == 1)
			menu_screen(w);
		else
			break;
		img_update(w);
		get_that_time(w);
	}
}

int		loose(t_env *w, t_map *m)
{
	int stop;

	stop = 0;
	main_pic(w, 2);
	w->txthead.x = 350;
	w->txthead.y = 400;
	type_str(w, w->txthead, "Press enter to retry", 0x12FFFFFF);
	m->newgame = 1;
	while (stop != 1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == 27)
				{
					w->menu.i = 1;
					stop = 1;
					m->game_over = 0;
					return(1);
				}
				if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
				{
					m->game_over = 0;
					m->player.hp = m->player.max_hp;
					stop = 1;
				}
			}
			if (w->event.type == SDL_WINDOWEVENT)
			{
				if (WINDOW == SDL_WINDOWEVENT_CLOSE)
					exit_game(w, w->m, 1);
			}
		}
		img_update(w);
	}
	return(0);
}

int		map_is_in_core(t_env *w, char *map)
{
	int 	i;
	int		found;

	i = 0;
	found = 0;
	w->nbmaps = get_nb_maps_in_core(w);
	if ((w->namesmaps = (char **)malloc(sizeof(char *) * (w->nbmaps + 1))) == NULL)
		set_error(w, w->m, 0, ft_strdup("map_is_in_core"));
	get_names_maps_in_core(w, w->namesmaps);
	w->namesmaps[w->nbmaps] = NULL;
	get_names_maps_in_core(w, w->namesmaps);
	while (w->namesmaps[i])
	{
		if (ft_strcmp(w->namesmaps[i], map) == 0)
		{	
			found = 1;
			break;
		}
		i++;
	}
	i = 0;
	while (w->namesmaps[i])
	{
		free(w->namesmaps[i]);
		i++;
	}
	free(w->namesmaps);
	if (found == 1)
		return (1);	
	else
		return (0);
}

int		change_lvl(t_env *w, t_map *m)
{
	int 	stop;
	float	time_lvl;

	stop = 0;
	w->dtime.end_lvl = SDL_GetTicks();
	time_lvl = w->dtime.end_lvl - w->dtime.start_lvl;
	if (time_lvl != 0)
		time_lvl = time_lvl / 1000;
	w->txthead.x = 350;
	w->txthead.y = 400;
	free(w->currmap);
	if (map_is_in_core(w, m->linklvl) == 1)
	{
		main_pic(w, 1);
		type_str(w, w->txthead, "Press enter to start next level", 0x12FFFFFF);
		w->currmap = ft_strdup(m->linklvl);
		w->menu.i = 5;
	}
	else
	{
		w->currmap = ft_strdup("hsh");
		w->menu.i = 1;
		m->change_lvl = 0;
		m->newgame = 1;
		w->txthead.x = 100;
		if (ft_strcmp(m->linklvl, "end_game") == 0)
		{
			main_pic(w, 1);
			type_str(w, w->txthead, "Congratulation, you finished the game ! press enter", 0x12FFFFFF);
		}
		else
			return (1);
	}
	type_str(w,  w->txtnxtline, "Level completed in :", 0x12FFFFFF);
	type_str(w,  w->txtnxtline, ft_strjoin(ft_ftoa(time_lvl, 4), " seconds"), 0x12FFFFFF);
	while (stop != 1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == 27)
				{
					w->menu.i = 1;
					m->newgame = 1;
					m->change_lvl = 0;
					stop = 1;
					return (1);
				}
				if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
				{
					m->newgame = 1;
					m->change_lvl = 0;
					stop = 1;
				}
			}
			if (w->event.type == SDL_WINDOWEVENT)
			{
				if (WINDOW == SDL_WINDOWEVENT_CLOSE)
					exit_game(w, w->m, 1);
			}
		}
		img_update(w);
	}
	if (w->menu.i == 1)
		return(1);
	return(0);
}

void	launch(t_env *w, t_map *m)
{	
	while (1)
	{
		if (w->menu.i < 2)
			main_menu(w, m);
		else if (w->menu.i == 2)
			maps(w);
		else if (w->menu.i == 3)
			settings(w);
		else if (w->menu.i == 4)
			level_editor_start(w);
		if (w->menu.i > 4)
		{
			if (m->game_over == 1)
			{
				if (loose(w, m) == 1)
					continue;
			}
			else if (m->change_lvl == 1)
			{
				if (change_lvl(w, m) == 1)
					continue;
			}
			if (m->newgame == 1)
			{
				if (parse_map_in_core(w, m, w->currmap) != 0)
					continue;
				w->dtime.start_lvl = SDL_GetTicks();
			}
			run(w, m);
		}
	}
}
