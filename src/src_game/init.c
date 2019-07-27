/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:03:15 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 19:07:09 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		img_update(t_env *w)
{
	if ((SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32))) < 0)
		set_error(w, w->m, 4, strdup_check(w, "SDL_UpdateTexture"));
	if ((SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL)) < 0)
		set_error(w, w->m, 4, strdup_check(w, "SDL_RenderCopy"));
	SDL_RenderPresent(w->rdr);
}

int			load_sounds(t_env *w, t_map *m)
{
	if (!(w->sound.musique = Mix_LoadMUS("./sounds/musique.wav")))
		return (-1);
	Mix_PlayMusic(w->sound.musique, -1);
	Mix_VolumeMusic(w->sound.volume);
	Mix_AllocateChannels(7);
	if (!(w->sound.jump = Mix_LoadWAV("./sounds/jump2.wav")))
		return (-1);
	if (!(w->sound.reload = Mix_LoadWAV("./sounds/reload.wav")))
		return (-1);
	if (!(w->sound.clic = Mix_LoadWAV("./sounds/clic.wav")))
		return (-1);
	if (!(w->sound.dammage = Mix_LoadWAV("./sounds/oof.wav")))
		return (-1);
	if (!(m->weap[0].shoot = Mix_LoadWAV("./sounds/M4.wav")))
		return (-1);
	if (!(m->weap[2].shoot = Mix_LoadWAV("./sounds/magnum.wav")))
		return (-1);
	if (!(m->weap[1].shoot = Mix_LoadWAV("./sounds/mp510.wav")))
		return (-1);
	Mix_VolumeChunk(w->sound.dammage, 110);
	Mix_VolumeChunk(w->sound.jump, 70);
	Mix_VolumeChunk(m->weap[1].shoot, 80);
	Mix_VolumeChunk(m->weap[0].shoot, 30);
	Mix_VolumeChunk(m->weap[2].shoot, 50);
	return (1);
}

int			init_window(t_env *w)
{
	if (w->window_mode == 1)
	{
		if (!(w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)))
			return (-1);
	}
	else if (w->window_mode == 0)
	{
		if (!(w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN)))
			return (-1);
	}
	return (0);
}

int			init_sdl(t_env *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (-1);
	if (init_window(w) == -1)
		return (-1);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (-1);
	if (!(w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC)))
		return (-1);
	if (!(w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT)))
		set_error(w, w->m, 0, strdup_check(w, "malloc error"));
	if (!(w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)))
		return (-1);
	clean_render(w, 0x12000000);
	img_update(w);
	return (0);
}
