/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sdl_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:40:41 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 19:07:17 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fit_to_editor(t_env *w, t_win *win)
{
	w->res.width = w->editor_res.width;
	w->res.height = w->editor_res.height;
	if (w->window_mode == 0)
		if ((SDL_SetWindowFullscreen(w->win, 0)) < 0)
			set_error(w, w->m, 4, strdup_check(w, "SDL Initialisation"));
	SDL_SetWindowResizable(w->win, SDL_FALSE);
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_SetWindowPosition(w->win, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	if (!(w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED)))
		clear_n_exit(w, win);
	if (!(w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT)))
		clear_n_exit(w, win);
	if (!(w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)))
		clear_n_exit(w, win);
	clean_render(w, 0x12000000);
	img_update(w);
}

void	set_full_screen(t_env *w)
{
	if (w->window_mode == 0)
	{
		if ((SDL_SetWindowFullscreen(w->win, SDL_WINDOW_FULLSCREEN)) < 0)
			set_error(w, w->m, 4, strdup_check(w, "SDL Initialisation"));
	}
	else
	{
		if ((SDL_SetWindowFullscreen(w->win, 0)) < 0)
			set_error(w, w->m, 4, strdup_check(w, "SDL Initialisation"));
	}
}

void	fit_to_game(t_env *w)
{
	w->res.width = w->game_res.width;
	w->res.height = w->game_res.height;
	set_full_screen(w);
	SDL_SetWindowResizable(w->win, SDL_TRUE);
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_SetWindowPosition(w->win, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	if (!(w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC)))
		set_error(w, w->m, 4, strdup_check(w, "SDL Initialisation"));
	if (!(w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT)))
		set_error(w, w->m, 0, strdup_check(w, "malloc error"));
	if (!(w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)))
		set_error(w, w->m, 4, strdup_check(w, "SDL Initialisation"));
	clean_render(w, 0x12000000);
	img_update(w);
}
