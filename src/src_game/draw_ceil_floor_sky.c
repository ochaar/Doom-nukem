/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_txtr_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:32:27 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/22 23:08:16 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	skybox(int x, t_env *w, t_work *work, t_texture text)
{
	int			y1;
	int			y2;
	int			tmpix;
	double		y_tex;
	double		x_tex;

	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (y2 >= y1)
	{
		while (y1 <= y2)
		{
			x_tex = (x * (text.w / 4)) / WIDTH + ((w->m->player.angle
				* (180 / PI)) * text.w) / 360;
			y_tex = (((y1 + w->m->yaw / 0.004 + 500) * text.h)
				/ HEIGHT / ((1576.f / (double)HEIGHT)));
			tmpix = (int)((int)y_tex % text.h) * text.w + ((int)x_tex % text.w);
			if (tmpix >= 0 && tmpix < text.h * text.w)
				w->pix[y1 * WIDTH + x] = text.pix[tmpix];
			else
				w->pix[y1 * WIDTH + x] = 0;
			y1++;
		}
	}
}

void	calc_map_pos_ceil(t_env *w, t_work *work, t_ceiling *c, int y1)
{
	c->side = y1 < work->cya ? work->yceil : work->yfloor;
	c->map_y = c->side * HEIGHT * (w->m->player.field_of_vision_v
		/ (double)HEIGHT) / ((HEIGHT / 2 - y1) - w->m->player.yaw
			* HEIGHT * (w->m->player.field_of_vision_v / (double)HEIGHT));
	c->map_x = c->map_y * (WIDTH / 2 - c->x) / (WIDTH
		* (w->m->player.field_of_vision_h / (double)WIDTH));
	c->rot_x = c->map_y * work->pcos + c->map_x * work->psin;
	c->rot_y = c->map_y * work->psin - c->map_x * work->pcos;
	c->map_x = c->rot_x + w->m->player.coor.x;
	c->map_y = c->rot_y + w->m->player.coor.y;
	test_sprite(w->m, c->map_x, c->map_y);
}

void	draw_ceiling_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_ceiling	c;
	int			y1;
	int			y2;

	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	c.x = x;
	if (y2 >= y1)
	{
		while (y1 <= y2)
		{
			if (y1 >= work->cya && y1 <= work->cyb && y2 != y1)
			{
				y1 = work->cyb;
				continue;
			}
			calc_map_pos_ceil(w, work, &c, y1);
			c.x_tex = (c.map_x * text->w / 6);
			c.y_tex = (c.map_y * text->w / 6);
			c.tmpix = (c.y_tex % text->h) * text->w + (c.x_tex % text->w);
			if (text->pix[c.tmpix] != TRANSPARENT)
				w->pix[y1 * WIDTH + x] = text->pix[c.tmpix];
			y1++;
		}
	}
}
