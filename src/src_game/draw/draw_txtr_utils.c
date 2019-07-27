/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_txtr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:35:44 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/22 23:08:34 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		dark_side(int color, t_work *work)
{
	int red;
	int gre;
	int blu;

	red = vmid((((color >> 16) & 0xff) - (work->z / 2)), 0, 255);
	gre = vmid((((color >> 8) & 0xff) - (work->z / 2)), 0, 255);
	blu = vmid((((color) & 0xff) - (work->z / 2)), 0, 255);
	return (0 << 24 | (red & 0xff) << 16 | (gre & 0xff) << 8 | (blu & 0xff));
}

void	draw_textured_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	while (d->y1 <= d->y2)
	{
		d->y_tex = (d->y_tex_pos / d->wall_height_from_bottom
			* d->wall_height_scale) * text->h;
		if (d->y_tex < 0)
			d->y_tex = 0;
		if (d->x_tex < 0)
			d->x_tex = 0;
		if (text->h >= 0 && text->w >= 0 && text->pix[((d->y_tex % text->h)
			* text->w) + (d->x_tex % text->w)] != TRANSPARENT)
		{
			d->color = text->pix[((d->y_tex % text->h) * text->w)
				+ (d->x_tex % text->w)];
			d->color = dark_side(d->color, work);
			w->pix[d->y1 * WIDTH + d->x] = d->color;
		}
		d->y_tex_pos++;
		d->y1++;
	}
}

void	check_start_end_tex(t_draw *d, t_work *work, t_texture *text)
{
	if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
	{
		work->start_x_tex = (work->t1.x - work->tt1.x) * text->w
			/ d->wall_width_scale / (work->tt2.x - work->tt1.x);
		work->end_x_tex = (work->t2.x - work->tt1.x) * text->w
			/ d->wall_width_scale / (work->tt2.x - work->tt1.x);
	}
	else
	{
		work->start_x_tex = (work->t1.z - work->tt1.z) * text->w
			/ d->wall_width_scale / (work->tt2.z - work->tt1.z);
		work->end_x_tex = (work->t2.z - work->tt1.z) * text->w
			/ d->wall_width_scale / (work->tt2.z - work->tt1.z);
	}
}
