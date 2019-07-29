/*BIG42HEADER*/

#include "doom.h"

void		img_update(t_env *w)
{
	SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL);
	SDL_RenderPresent(w->rdr);
}

int			load_sounds(t_env *w, t_map *m)
{
	if (!(w->sound.musique = Mix_LoadMUS("./sounds/musique.wav")))
		return (-1);
   	Mix_PlayMusic(w->sound.musique, -1);
	Mix_VolumeMusic(w->sound.volume);
	Mix_AllocateChannels(10);
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

int			init_sdl(t_env *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (-1);
	if (w->window_mode == 1)
	{
		w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	}
	else if (w->window_mode == 0)
	{
		w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (-1);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	clean_render(w, 0x12000000);
	img_update(w);
	return (0);
}

void			init_sprite_tab(t_map *m)
{
	int i;

	i = 0;
	m->tab = (double**)malloc(sizeof(double*) * (m->sprite_map_count
		+ m->ennemy_count));
	while (i < m->sprite_map_count + m->ennemy_count)
	{
		m->tab[i] = (double*)malloc(sizeof(double) * 3);
		i++;
	}
}
