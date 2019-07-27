/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:44:25 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:58:53 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_struct_helper(t_win *win)
{
	win->asset = 0;
	win->drawtriangles = 0;
	win->place = 0;
	win->tab = NULL;
	win->changemode = 0;
	win->number = 0;
	win->index_dot = 0;
	win->same_dots = 0;
	win->tab_index = 0;
	win->triangle_sector = 0;
	win->check_textures = 0;
	win->texture_choice = 0;
	win->put_texture = 0;
	win->texture_overed_sector = -1;
	win->texture_index = 0;
	win->blackbox_x = 253;
	win->txtr_input_type = 0;
	win->param_index = 0;
	win->hp_value = 100;
	win->gravity_value = 5;
	win->god_value = 0;
	win->neighbour_index = 0;
}

static int	init_assets(t_env *w, t_win *win)
{
	win->map_ui = w->m->fire;
	win->asset_sprite = w->m->sprite[23];
	win->asset_tmp = w->m->sprite[0];
	win->player_start = w->m->sprite[23];
	win->inventory = w->m->hud2;
	win->slot0 = w->texturing[0];
	win->slot1 = w->texturing[1];
	win->slot2 = w->texturing[2];
	win->slot3 = w->texturing[3];
	win->slot4 = w->texturing[4];
	win->blackbox = w->m->whitebox;
	win->hud_box = 0;
	win->building_hud = w->m->hud;
	win->lst = NULL;
	win->paramtxt = NULL;
	win->paramvaluetxt = NULL;
	return (0);
}

static int	init_struct(t_win *win)
{
	win->drawing = 0;
	win->sector = 0;
	win->link = 0;
	win->left_click = 0;
	win->mode = 0;
	win->moving = 0;
	win->tmp = NULL;
	win->tmpasset = NULL;
	win->lst = NULL;
	win->lstlst = NULL;
	win->lstast = NULL;
	win->color = 255255255;
	win->overed_sector = -1;
	win->triangles = NULL;
	if (!(win->cursor = SDL_CreateSystemCursor(ARROW)))
		clear_n_exit(win->wo, win);
	init_struct_helper(win);
	return (0);
}

int			init2(t_env *w, t_win *win)
{
	if (!(win->itoastr = (char *)malloc(sizeof(char) * 12)))
		clear_n_exit(w, win);
	if (init_struct(win) != 0)
		clear_n_exit(w, win);
	if (init_assets(w, win) != 0)
		clear_n_exit(w, win);
	init_dst(win);
	return (0);
}
