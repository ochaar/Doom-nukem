/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 02:22:39 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 02:23:56 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_queue(t_map *m, t_reader *read, int *renderedsectors)
{
	read->now = *read->tail;
	if (++read->tail == read->queue + m->maxrenderedsector)
		read->tail = read->queue;
	if (renderedsectors[read->now.sectorno] & (m->maxrenderedsector + 1))
		return (-1);
	return (0);
}

void	init_draw(t_env *w, t_reader *read, t_work *work)
{
	int x;

	x = 0;
	clear_sprite(w->m);
	read->head = read->queue;
	read->tail = read->queue;
	while (x < WIDTH)
	{
		work->ytop[x] = 0;
		work->ybot[x] = HEIGHT - 1;
		x++;
	}
	read->head->sectorno = w->m->player.sector;
	read->head->sx1 = 0;
	read->head->sx2 = WIDTH - 1;
	if (++read->head == read->queue + w->m->maxrenderedsector)
		read->head = read->queue;
	work->nearz = 0.0000000001;
	work->farz = 5;
	work->nearside = 0.0000000001;
	work->farside = 20.f;
	w->i = 0;
}

void	draw(t_env *w, t_map *m)
{
	int			point;
	int			x;
	t_work		work;
	t_reader	read;
	int			renderedsectors[m->sector_count];

	init_draw(w, &read, &work);
	x = -1;
	while (++x < w->m->sector_count)
		renderedsectors[x] = 0;
	while (read.head != read.tail)
	{
		if (init_queue(m, &read, renderedsectors) == -1)
			continue;
		++renderedsectors[read.now.sectorno];
		work.nosector = read.now.sectorno;
		point = 0;
		while (point < m->sector[read.now.sectorno].wall_count)
		{
			render_wall(&read, &work, w, point);
			point++;
		}
		++renderedsectors[read.now.sectorno];
	}
	count_sprite(w, m);
}
