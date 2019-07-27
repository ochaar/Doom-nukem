/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:11 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 08:59:09 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	event_menu_maps(t_env *w)
{
	if (w->event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_ESCAPE)
			w->menu.i = vmax(-1, w->menu.i - 1);
		if (KEY == SDLK_RETURN || KEY == SDLK_KP_ENTER)
		{
			free(w->currmap);
			w->currmap = strdup_check(w, w->namesmaps[w->menu.k]);
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

void	aff_maps_2(t_env *w)
{
	t_dot			dot;
	int				i;
	int				j;
	int				start;
	unsigned int	color;

	j = -1;
	start = 1;
	i = ((w->menu.k - 5) >= 0) ? (w->menu.k - 5) : w->nbmaps + (w->menu.k - 5);
	dot = fill_t_dot(WIDTH / 2 - 50, 140);
	while (++j < 10)
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
	}
}

void	aff_maps_1(t_env *w)
{
	int				i;
	t_dot			dot;
	unsigned int	color;

	i = 0;
	dot = fill_t_dot(WIDTH / 2 - 50, 140);
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

void	get_maps_infos(t_env *w)
{
	w->nbmaps = get_nb_maps_in_core(w);
	if ((w->namesmaps = (char **)malloc(sizeof(char *)
		* (w->nbmaps + 1))) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "menu_maps"));
	get_names_maps_in_core(w, w->m, w->namesmaps);
	w->namesmaps[w->nbmaps] = NULL;
}

void	menu_maps(t_env *w)
{
	t_dot	dot;

	w->menu.k = 0;
	dot = fill_t_dot(10, 10);
	get_maps_infos(w);
	while (1)
	{
		main_pic(w, 1);
		type_str(w, dot, "MAPS :\n", 0xFFFFFFFF);
		if (w->nbmaps > 0 && w->nbmaps <= 10)
			aff_maps_1(w);
		else if (w->nbmaps > 10)
			aff_maps_2(w);
		while (SDL_PollEvent(&w->event))
			event_menu_maps(w);
		if (w->menu.i != 2)
		{
			ft_memreg(w->namesmaps);
			break ;
		}
		img_update(w);
	}
}
