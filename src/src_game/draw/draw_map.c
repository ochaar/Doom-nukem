/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:11:26 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 22:18:55 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_txtr_pix(t_env *w, int x, int y, Uint32 color)
{
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
		w->pix[y * WIDTH + x] = color;
}

void	set_txtr_dot(t_env *w, int x, int y, Uint32 color)
{
	int		i;

	i = 0;
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		w->pix[y * WIDTH + x] = color;
		while (i < 3)
		{
			if (y - i >= 0)
				w->pix[(y - i) * WIDTH + x] = color;
			if (x - i >= 0)
				w->pix[y * WIDTH + (x - i)] = color;
			if (y + i < HEIGHT)
				w->pix[(y + i) * WIDTH + x] = color;
			if (x + i < WIDTH)
				w->pix[y * WIDTH + (x + i)] = color;
			i++;
		}
	}
}

void	calc_draw_map(t_env *w, t_work *work, int sector, int point)
{
	work->winwidth = WIDTH;
	work->winheight = HEIGHT;
	work->v1.x = (w->m->sector[sector].dot[point].x - w->m->player.coor.x);
	work->v1.y = (w->m->sector[sector].dot[point].y - w->m->player.coor.y);
	work->v2.x = (w->m->sector[sector].dot[point + 1].x - w->m->player.coor.x);
	work->v2.y = (w->m->sector[sector].dot[point + 1].y - w->m->player.coor.y);
	work->t1.x = -(work->v1.x * w->m->player.anglesin - work->v1.y
		* w->m->player.anglecos) * 10 + (work->winwidth / 2);
	work->t1.y = -(work->v1.x * w->m->player.anglecos + work->v1.y
		* w->m->player.anglesin) * 10 + (work->winheight / 2);
	work->t2.x = -(work->v2.x * w->m->player.anglesin - work->v2.y
		* w->m->player.anglecos) * 10 + (work->winwidth / 2);
	work->t2.y = -(work->v2.x * w->m->player.anglecos + work->v2.y
		* w->m->player.anglesin) * 10 + (work->winheight / 2);
	if (w->m->sector[sector].network[point] < 0)
		vect_ab(work->t1, work->t2, w, 0x12FF0000);
}

void	draw_map(t_env *w, t_map *m)
{
	t_work	work;
	int		sector;
	int		point;

	clean_render(w, 0x12CECECE);
	work.p1.x = WIDTH / 2;
	work.p1.y = HEIGHT / 2 - 1;
	work.p2.x = work.p1.x;
	work.p2.y = work.p1.y - 9;
	set_txtr_dot(w, work.p1.x, work.p1.y + 1, 0x12BF3030);
	vect_ab(work.p1, work.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			calc_draw_map(w, &work, sector, point);
			point++;
		}
		sector++;
	}
}
