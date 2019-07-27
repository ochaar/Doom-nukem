/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:15:26 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 22:30:55 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		img_to_screen(t_env *w, t_texture texture, t_img img)
{
	t_scalling	s;

	get_scalling(&img, &s, texture.w, texture.h);
	if (init_and_check_to_screen(&s, w, &img) == 0)
		return (0);
	while (img.y < s.maxy && (int)s.x_tex * (int)s.y_tex < texture.len)
	{
		img.x = s.x_tmp;
		s.x_tex = s.x_tex_tmp;
		while (img.x < s.maxx && (int)s.x_tex * (int)s.y_tex < texture.len)
		{
			if (test_limits_to_screen(&img, &s, w) == 1)
			{
				s.tmpix = (int)s.y_tex * texture.w + (int)s.x_tex;
				if (texture.pix[s.tmpix] != TRANSPARENT)
					w->pix[img.y * WIDTH + img.x] = texture.pix[s.tmpix];
			}
			s.x_tex += s.step_x_tex;
			img.x++;
		}
		s.y_tex += s.step_y_tex;
		img_sequential_frame(w, img.y);
		img.y++;
	}
	return (1);
}

int		sprt_to_screen(t_env *w, t_sprite sprite, t_img img)
{
	t_scalling	s;

	get_scalling(&img, &s, sprite.w, sprite.h);
	if (init_and_check_to_screen(&s, w, &img) == 0)
		return (0);
	while (img.y < s.maxy && (int)s.x_tex * (int)s.y_tex < sprite.len)
	{
		img.x = s.x_tmp;
		s.x_tex = s.x_tex_tmp;
		while (img.x < s.maxx && (int)s.x_tex * (int)s.y_tex < sprite.len)
		{
			if (test_limits_to_screen(&img, &s, w) == 1)
			{
				s.tmpix = (int)s.y_tex * sprite.w + (int)s.x_tex;
				if (sprite.pix[s.tmpix] != TRANSPARENT)
					w->pix[img.y * WIDTH + img.x] = sprite.pix[s.tmpix];
			}
			s.x_tex += s.step_x_tex;
			img.x++;
		}
		s.y_tex += s.step_y_tex;
		img_sequential_frame(w, img.y);
		img.y++;
	}
	return (1);
}

int		get_tmpix_scaled(t_sprite sprite, t_img img)
{
	double		step_x_tex;
	double		step_y_tex;

	get_scalling(&img, NULL, sprite.w, sprite.h);
	step_x_tex = (double)sprite.w / (double)img.w;
	step_y_tex = (double)sprite.h / (double)img.h;
	return ((int)(step_x_tex * img.x) + ((int)(step_y_tex * img.y) * sprite.w));
}

void	safe_char_to_screen(t_env *w, t_texture texture, int x, int y)
{
	int			i;
	int			tmpix;
	int			ox;
	int			oy;

	i = y * WIDTH + x;
	ox = 0;
	oy = 0;
	while (ox * oy < texture.len && i < WIDTH * HEIGHT)
	{
		ox = 0;
		while (ox < texture.w)
		{
			if ((x + ox >= 0 && x + ox < WIDTH)
				&& (y + oy >= 0 && y + oy < HEIGHT))
			{
				tmpix = oy * texture.w + ox;
				if (texture.pix[tmpix] != texture.pix[0])
					w->pix[(y + oy) * WIDTH + (x + ox)] = w->txt.color;
			}
			i++;
			ox++;
		}
		oy++;
	}
}
