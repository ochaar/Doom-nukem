/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:19:05 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 16:17:51 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	inventory(t_env *w, t_map *m, t_dot dot)
{
	t_img	img;
	
	dot.x = 115;
	if (m->player.take[PH] == 1)
	{
		ft_light_itoa(m->weap[PH].actu_ammo, m->player.stractu_ammo);
		type_str(w, dot, m->player.stractu_ammo, 0x12000000);
	}
	else
		type_str(w, dot, "0", 0x12000000);
	if (m->player.take[0] == 1)
	{
		img = fill_t_img(319, HEIGHT - 58, 64, 48);
		sprt_to_screen(w, m->sprite[0], img);
	}
	if (m->player.take[1] == 1)
	{
		img = fill_t_img(399, HEIGHT - 60, 64, 48);
		sprt_to_screen(w, m->sprite[1], img);
	}
	if (m->player.take[2] == 1)
	{
		img = fill_t_img(480, HEIGHT - 54, 64, 0);
		sprt_to_screen(w, m->sprite[2], img);
	}
	if (m->player.take[3] == 1)
	{
		img = fill_t_img(560, HEIGHT - 54, 64, 0);
		sprt_to_screen(w, m->sprite[22], img);
	}
}

void	ft_hud(t_env *w, t_map *m)
{
	t_dot	dot;

	dot.x = WIDTH / 2 - m->hud.w / 2;
	dot.y = HEIGHT - m->hud.h;
	safe_texture_to_screen(w, m->hud, dot.x, dot.y);
	dot.x = 10;
	dot.y = 10;
	type_str(w, dot, "HP : ", 0x12FF0000);
	ft_light_itoa(m->player.hp, m->player.strhp);
	type_str(w, w->txtnxtto, m->player.strhp, 0x12FF0000);
	dot.y = HEIGHT - 30;
	type_str(w, dot, "AMMO :   /", 0x12000000);
	if (PH == 1)
		ft_light_itoa(m->player.bullet[1], m->player.strbullet);
	else
		ft_light_itoa(m->player.bullet[0], m->player.strbullet);
	type_str(w, w->txtnxtto, m->player.strbullet, 0x12000000);
	inventory(w, m, dot);
	dot.x = WIDTH - 130;
	dot.y = 10;
	type_str(w, dot, "FPS : ", 0x12000000);
	if (w->dtime.stime == 0)
		ft_light_itoa(w->dtime.fps, m->player.fps);
	type_str(w, w->txtnxtto, m->player.fps, 0x12000000);
}

void	sequential_frame(t_env *w, t_map *m)
{
	w->txthead.x = 265;
	w->txthead.y = 236;
	type_str(w, w->txthead, "sequential frame rendering started.", 0xFF000000);
	img_update(w);
	SDL_Delay(1500);
	clean_render(w, 0xFF000000);
	type_str(w, w->txthead, "sequential frame rendering started.", 0xFFFFFFFF);
	img_update(w);
	SDL_Delay(500);
	clean_render(w, 0xFF000000);
	img_update(w);
	game_img(w, m);
	w->sequential_frame = 0;
	w->txthead.x = 313;
	type_str(w, w->txthead, "back to normal in 3 seconds...", 0xFF0000FF);
	img_update(w);
	SDL_Delay(1000);
	game_img(w, m);
	type_str(w, w->txthead, "back to normal in 2 seconds...", 0xFFFFFFFF);
	img_update(w);
	SDL_Delay(1000);
	game_img(w, m);
	type_str(w, w->txthead, "back to normal in 1 seconds...", 0xFFFF0000);
	img_update(w);
	SDL_Delay(1000);
}
