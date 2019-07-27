/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:58:19 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 18:25:22 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_walls(t_work *work, t_env *w, int x)
{
	work->starty = work->cya;
	work->stopy = work->cyb;
	if (w->texturing[w->m->sector[work->nosector].texturing[2]].trsp == 1)
	{
		skybox(x, w, work,
			w->texturing[w->m->sector[work->nosector].texturing[5]]);
		draw_wall_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[2]]);
	}
	else
		draw_wall_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[2]]);
}

void	lets_draw_networks(t_work *work, t_env *w, int x)
{
	if (w->texturing[w->m->sector[work->nosector].texturing[3]].trsp == 1)
	{
		skybox(x, w, work,
			w->texturing[w->m->sector[work->nosector].texturing[5]]);
		draw_high_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[3]]);
	}
	else
		draw_high_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[3]]);
	work->starty = work->cnyb + 1;
	if (work->cnyb < work->cya)
		work->starty = work->cya + 1;
	work->stopy = work->cyb;
	if (w->texturing[w->m->sector[work->nosector].texturing[4]].trsp == 1)
	{
		skybox(x, w, work,
			w->texturing[w->m->sector[work->nosector].texturing[5]]);
		draw_low_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[4]]);
	}
	else
		draw_low_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[4]]);
}

void	draw_networks(t_work *work, t_env *w, int x)
{
	work->nya = (x - work->x1) * (work->ny2a - work->ny1a)
		/ (work->x2 - work->x1) + work->ny1a;
	work->nyb = (x - work->x1) * (work->ny2b - work->ny1b)
		/ (work->x2 - work->x1) + work->ny1b;
	work->cnya = vmid(work->nya, work->ytop[x], work->ybot[x]);
	work->cnyb = vmid(work->nyb, work->ytop[x], work->ybot[x]);
	if (work->z > 255)
		work->z = 255;
	work->starty = work->cya;
	work->stopy = work->cnya - 1;
	lets_draw_networks(work, w, x);
}

void	init_draw_ceiling_n_floor(t_work *work, int x)
{
	work->ya = (x - work->x1) * (work->y2a - work->y1a)
		/ (work->x2 - work->x1) + work->y1a;
	work->yb = (x - work->x1) * (work->y2b - work->y1b)
		/ (work->x2 - work->x1) + work->y1b;
	work->cya = vmid(work->ya, work->ytop[x], work->ybot[x]);
	work->cyb = vmid(work->yb, work->ytop[x], work->ybot[x]);
	work->starty = work->ytop[x];
	work->stopy = work->cya - 1;
}

void	draw_ceiling_n_floor(t_work *work, t_env *w, int x)
{
	init_draw_ceiling_n_floor(work, x);
	if (w->m->sector[work->nosector].texturing[1] == 0
		|| w->texturing[w->m->sector[work->nosector].texturing[1]].trsp == 1)
	{
		skybox(x, w, work,
			w->texturing[w->m->sector[work->nosector].texturing[5]]);
		if (w->texturing[w->m->sector[work->nosector].texturing[1]].trsp == 1)
			draw_ceiling_line_t(x, w, work,
				&w->texturing[w->m->sector[work->nosector].texturing[1]]);
	}
	else
		draw_ceiling_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[1]]);
	work->starty = work->cyb + 1;
	work->stopy = work->ybot[x];
	if (w->texturing[w->m->sector[work->nosector].texturing[0]].trsp == 1)
	{
		skybox(x, w, work,
			w->texturing[w->m->sector[work->nosector].texturing[5]]);
		draw_ceiling_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[0]]);
	}
	else
		draw_ceiling_line_t(x, w, work,
			&w->texturing[w->m->sector[work->nosector].texturing[0]]);
}
