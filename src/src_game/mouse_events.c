/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:51:49 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 16:51:51 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		buttonup_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT)
		m->player.shooting = 0;
	if (BUTTON == SDL_BUTTON_RIGHT)
	{
		m->player.field_of_vision_h = w->mem_field_of_vision_h;
		m->player.field_of_vision_v = w->mem_field_of_vision_v;
		m->player.aiming = 0;
	}
}

void		buttondown_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT && m->player.take[PH] == 1)
		m->player.shooting = 1;
	if (BUTTON == SDL_BUTTON_RIGHT && m->player.take[PH] == 1)
	{
		m->player.field_of_vision_h = 2 * w->mem_field_of_vision_h;
		m->player.field_of_vision_v = 2 * w->mem_field_of_vision_v;
		m->player.aiming = 1;
	}
}

void		motion_events(t_env *w, t_map *m)
{
	look_around(w, m);
	if (m->player.display == 0)
		SDL_WarpMouseInWindow(w->win, WIDTH / 2, HEIGHT / 2);
	move_player(0, 0, m);
}
