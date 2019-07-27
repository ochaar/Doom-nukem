/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:47:03 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 14:05:04 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		reset_map(t_map *m)
{
	ft_free_tab(m);
	ft_free_sector(m);
	if (m->dot != NULL)
	{
		free(m->dot);
		m->dot = NULL;
	}
	ft_free_sprt(m);
	if (m->ennemy != NULL)
	{
		free(m->ennemy);
		m->ennemy = NULL;
	}
	if (m->linklvl != NULL)
	{
		free(m->linklvl);
		m->linklvl = NULL;
	}
	m->endsector = -1;
	m->change_lvl = 0;
	m->newgame = 0;
}

void		set_screen_res(t_env *w, char *aspect)
{
	w->window_res = ft_atoi(aspect);
	if (w->window_res == 0)
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
	else if (w->window_res == 1)
	{
		w->res.width = 1920;
		w->res.height = 1080;
	}
	else
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
	w->game_res.width = w->res.width;
	w->game_res.height = w->res.height;
}

void		set_null(t_env *w)
{
	w->win = NULL;
	w->rdr = NULL;
	w->sound.dammage = NULL;
	w->sound.volume = 80;
	w->sound.musique = NULL;
	w->sound.jump = NULL;
	w->sound.reload = NULL;
	w->sound.clic = NULL;
	w->texturing = NULL;
	w->pix = NULL;
	w->inkeys = NULL;
	w->txtr = NULL;
	w->ascii = NULL;
}

void		set_int(t_env *w)
{
	w->nbmaps = 0;
	w->window_mode = -1;
	w->i = 0;
	w->asciichk = 0;
	w->asciino = -1;
	w->stopread = 0;
	w->invert = 1;
	w->random = 0;
	w->sequential_draw = 0;
	w->menu.i = 0;
	w->menu.j = 0;
	w->dtime.fps = 0;
	w->dtime.start = 0;
	w->dtime.end = 0;
	w->dtime.ctime = 0;
	w->dtime.otime = 0;
	w->dtime.etime = 0;
	w->dtime.walk = 0;
	w->dtime.dead = 0;
	w->dtime.shootime = 0;
	w->dtime.stime = 0;
	w->dtime.start_lvl = 0;
	w->dtime.end_lvl = 0;
	w->mousesp_menu = 0;
}

void		set_w(t_env *w, int ac)
{
	set_null(w);
	set_int(w);
	w->ac = ac;
	w->currmap = strdup_check(w, "hsh");
	w->editor_res.width = WIN_X;
	w->editor_res.height = WIN_Y;
	if (!(w->light_nb = (char *)malloc(sizeof(char) * 12)))
		set_error(w, w->m, 0, strdup_check(w, "light_nb"));
	ft_light_itoa(0, w->light_nb);
	w->main_pic[0] = pre_init_texture(w->res.width, w->res.height);
	w->main_pic[1] = pre_init_texture(w->res.width, w->res.height);
	w->main_pic[2] = pre_init_texture(w->res.width, w->res.height);
	w->txthead.x = 0;
	w->txthead.y = 0;
	w->txtnxtline.x = 0;
	w->txtnxtline.y = 0;
	w->txtnxtto.x = 0;
	w->txtnxtto.y = 0;
	w->texturingno = 0;
	w->window_mode_menu = 0;
	w->window_res_menu = 0;
	w->fov_h_menu = 0;
	w->fov_v_menu = 0;
	w->corenbl = 0;
}
