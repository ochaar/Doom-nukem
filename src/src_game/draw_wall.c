/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 23:04:04 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/22 23:15:39 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	do_normal_wall_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	d->wall_height_from_bottom = work->yb - work->starty;
	d->wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
	d->wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
	check_start_end_tex(d, work, text);
	d->y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1)
		- (d->x - work->x1)) / (work->x2 - work->x1) - work->y2a;
	d->x_tex = ((work->start_x_tex * ((work->x2 - d->x) * work->t2.z)
		+ work->end_x_tex * ((d->x - work->x1) * work->t1.z)) / ((work->x2
			- d->x) * work->t2.z + (d->x - work->x1) * work->t1.z));
	if ((work->y1a < 0 || work->y2a < 0) && d->y1 == 0)
	{
		d->wall_height_from_bottom += d->y_tex_start;
		d->y_tex_pos += d->y_tex_start;
		draw_textured_line(d, w, work, text);
	}
	else
	{
		d->wall_height_from_bottom = work->yb - work->ya;
		draw_textured_line(d, w, work, text);
	}
}

void	do_special_wall_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	d->wall_height_from_bottom = (work->yb - work->ya)
		- (work->starty - work->ya);
	d->wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
	d->wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
	check_start_end_tex(d, work, text);
	d->y_tex_start = (work->starty - work->ya);
	d->x_tex = ((work->start_x_tex * ((work->x2 - d->x) * work->t2.z)
		+ work->end_x_tex * ((d->x - work->x1) * work->t1.z)) / ((work->x2
			- d->x) * work->t2.z + (d->x - work->x1) * work->t1.z));
	d->wall_height_from_bottom += d->y_tex_start;
	d->y_tex_pos += d->y_tex_start;
	draw_textured_line(d, w, work, text);
}

void	draw_wall_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_draw	d;

	d.x = x;
	d.y_tex_pos = 0;
	d.y1 = vmid(work->starty, 0, HEIGHT - 1);
	d.y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (d.y2 > d.y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == d.y1
			&& vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
			do_special_wall_line(&d, w, work, text);
		else
			do_normal_wall_line(&d, w, work, text);
	}
}
