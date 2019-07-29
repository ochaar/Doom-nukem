/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:26:31 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 17:38:39 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			clear_n_exit(t_win *win, int error)
{
	//put_error(error);
	//if (win->surface != NULL)
	//	SDL_FreeSurface(win->surface);
	//if (win->renderer != NULL)
	//	SDL_DestroyRenderer(win->renderer);
	//if (win->window != NULL)
	//	SDL_DestroyWindow(win->window);
	(void)win;
	if (error > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int		level_editor_start(t_env *w)
{
	t_win	win;

	fit_to_editor(w);
	init2(w, &win);
	loop_play(w, &win);
	w->menu.i = 1;
	// fit_to_game(w);
	return (EXIT_SUCCESS);
}
