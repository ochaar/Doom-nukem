/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 02:24:04 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 18:24:13 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	update_network_queue(t_env *w, t_work *work, t_reader *read)
{
	if (work->network >= 0 && work->endx >= work->startx && (read->head
		+ w->m->maxrenderedsector + 1 - read->tail) % w->m->maxrenderedsector)
	{
		read->head->sectorno = work->network;
		read->head->sx1 = work->startx;
		read->head->sx2 = work->endx;
		if (++read->head == read->queue + w->m->maxrenderedsector)
			read->head = read->queue;
	}
}

void	calc_transformation(t_env *w, t_work *work, t_reader *read)
{
	work->y1a = HEIGHT / 2 - (int)(yaw(work->yceil, work->t1.z, w->m)
		* work->yscale1);
	work->y2a = HEIGHT / 2 - (int)(yaw(work->yceil, work->t2.z, w->m)
		* work->yscale2);
	work->y1b = HEIGHT / 2 - (int)(yaw(work->yfloor, work->t1.z, w->m)
		* work->yscale1);
	work->y2b = HEIGHT / 2 - (int)(yaw(work->yfloor, work->t2.z, w->m)
		* work->yscale2);
	work->ny1a = HEIGHT / 2 - (int)(yaw(work->nyceil, work->t1.z, w->m)
		* work->yscale1);
	work->ny2a = HEIGHT / 2 - (int)(yaw(work->nyceil, work->t2.z, w->m)
		* work->yscale2);
	work->ny1b = HEIGHT / 2 - (int)(yaw(work->nyfloor, work->t1.z, w->m)
		* work->yscale1);
	work->ny2b = HEIGHT / 2 - (int)(yaw(work->nyfloor, work->t2.z, w->m)
		* work->yscale2);
	work->startx = vmax(work->x1, read->now.sx1);
	work->endx = vmin(work->x2, read->now.sx2);
}

void	calc_vertical_and_network(t_env *w, t_work *work, t_reader *read, int p)
{
	work->yceil = w->m->sector[read->now.sectorno].ceiling
		- w->m->player.coor.z;
	work->yfloor = w->m->sector[read->now.sectorno].floor - w->m->player.coor.z;
	work->network = w->m->sector[read->now.sectorno].network[p];
	work->nyceil = 0;
	work->nyfloor = 0;
	if (work->network >= 0)
	{
		work->nyceil = w->m->sector[work->network].ceiling
			- w->m->player.coor.z;
		work->nyfloor = w->m->sector[work->network].floor - w->m->player.coor.z;
	}
}

void	init_render_wall(t_map *m, t_work *work, t_reader *read, int point)
{
	work->wall_width = pythagore((m->sector[read->now.sectorno].dot[point
		+ 1].x - m->sector[read->now.sectorno].dot[point].x),
			(m->sector[read->now.sectorno].dot[point + 1].y
				- m->sector[read->now.sectorno].dot[point].y));
	work->v1.x = m->sector[read->now.sectorno].dot[point + 0].x - PL_X;
	work->v1.y = m->sector[read->now.sectorno].dot[point + 0].y - PL_Y;
	work->v2.x = m->sector[read->now.sectorno].dot[point + 1].x - PL_X;
	work->v2.y = m->sector[read->now.sectorno].dot[point + 1].y - PL_Y;
	work->pcos = PL_AC;
	work->psin = PL_AS;
	work->t1.x = work->v1.x * work->psin - work->v1.y * work->pcos;
	work->t1.z = work->v1.x * work->pcos + work->v1.y * work->psin;
	work->t2.x = work->v2.x * work->psin - work->v2.y * work->pcos;
	work->t2.z = work->v2.x * work->pcos + work->v2.y * work->psin;
	work->tt1.x = work->t1.x;
	work->tt1.z = work->t1.z;
	work->tt2.x = work->t2.x;
	work->tt2.z = work->t2.z;
}

int		render_wall(t_reader *read, t_work *work, t_env *w, int point)
{
	init_render_wall(w->m, work, read, point);
	if (work->t1.z < 0 && work->t2.z < 0)
		return (-1);
	if (work->t1.z < 0 || work->t2.z < 0)
	{
		init_clamp_wall(work);
		clamp_wall_1(work);
		clamp_wall_2(work);
	}
	calc_x1_to_x2(w, work);
	if (work->x1 >= work->x2 || work->x2 < read->now.sx1
		|| work->x1 > read->now.sx2)
		return (-1);
	calc_vertical_and_network(w, work, read, point);
	calc_transformation(w, work, read);
	if (work->endx - work->startx > 10)
		calcul_render_mthrd(w, *work, work->ybot, work->ytop);
	else
		calcul_render_no_mthrd(w, work);
	update_network_queue(w, work, read);
	sequential_draw_render(w);
	return (0);
}
