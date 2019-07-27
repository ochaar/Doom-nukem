/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:57:36 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 22:16:38 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	calc_draw_mini_map(t_env *w, t_work *work, int sector, int point)
{
	work->v1.x = (w->m->sector[sector].dot[point].x - w->m->player.coor.x);
	work->v1.y = (w->m->sector[sector].dot[point].y - w->m->player.coor.y);
	work->v2.x = (w->m->sector[sector].dot[point + 1].x - w->m->player.coor.x);
	work->v2.y = (w->m->sector[sector].dot[point + 1].y - w->m->player.coor.y);
	work->t1.x = WIDTH - ((work->v1.x * w->m->player.anglesin - work->v1.y
		* w->m->player.anglecos) * 10 + (WIDTH / 2)) / 3;
	work->t1.y = HEIGHT - ((work->v1.x * w->m->player.anglecos + work->v1.y
		* w->m->player.anglesin) * 10 + (HEIGHT / 2)) / 3;
	work->t2.x = WIDTH - ((work->v2.x * w->m->player.anglesin - work->v2.y
		* w->m->player.anglecos) * 10 + (WIDTH / 2)) / 3;
	work->t2.y = HEIGHT - ((work->v2.x * w->m->player.anglecos + work->v2.y
		* w->m->player.anglesin) * 10 + (HEIGHT / 2)) / 3;
	if (w->m->sector[sector].network[point] < 0)
		vect_ab(work->t1, work->t2, w, 0x12FF0000);
}

void	draw_mini_map(t_env *w, t_map *m)
{
	t_work	work;
	int		sector;
	int		point;

	work.p1.x = WIDTH - (WIDTH / 2) / 3;
	work.p1.y = HEIGHT - (HEIGHT / 2 - 1) / 3;
	work.p2.x = (work.p1.x);
	work.p2.y = (work.p1.y - 3);
	set_txtr_dot(w, work.p1.x, work.p1.y + 1, 0x12BF3030);
	vect_ab(work.p1, work.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			calc_draw_mini_map(w, &work, sector, point);
			point++;
		}
		sector++;
	}
}
