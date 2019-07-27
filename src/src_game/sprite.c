/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:00:14 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 19:01:04 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cal_sprt	calcul_sprite_ennemy(t_env *w, t_map *m, int x, double ratio)
{
	t_cal_sprt	tmp;

	tmp.v1x = m->ennemy[x].coor.x - PL_X;
	tmp.v1y = m->ennemy[x].coor.y - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	if (m->ennemy[x].range > 6)
		m->ennemy[x].range = 6;
	tmp.zoom = m->ennemy[x].range;
	if (m->player.aiming == 1)
		tmp.zoom *= 2;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1
		+ (m->sprite[m->ennemy[x].index].w / 2 * tmp.zoom * ratio));
	tmp.y1a = HEIGHT / 2 - (int)(yaw((m->ennemy[x].coor.z - m->ennemy[x].height
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1)
				- (m->sprite[m->ennemy[x].index].h * tmp.zoom * ratio);
	tmp.ratio = ratio;
	return (tmp);
}

void		hit_box(t_env *w, t_map *m, int x, t_cal_sprt d)
{
	double			len;
	int				tmpix;
	t_img			img;

	img = fill_t_img((WIDTH / 2 - (int)d.x1), (HEIGHT / 2 - (int)d.y1a),
		(m->sprite[m->ennemy[x].index].w * d.zoom * d.ratio), 0);
	tmpix = get_tmpix_scaled(m->sprite[m->ennemy[x].index], img);
	len = m->sprite[m->ennemy[x].index].w * d.zoom * d.ratio;
	if ((d.x1 <= WIDTH / 2 && d.x1 >= WIDTH / 2 - len)
		&& (d.y1a <= HEIGHT / 2 && d.y1a >= HEIGHT / 2 - len)
			&& m->sprite[m->ennemy[x].index].pix[tmpix] != TRANSPARENT
				&& m->ennemy[x].is_dead != 1)
	{
		if (m->weap[PH].ammo_type == 1)
			m->ennemy[x].dead = 1;
		else
		{
			m->ennemy[x].nb_ammo++;
			m->ennemy[x].touche = 1;
			if (m->ennemy[x].nb_ammo % 4 == 0)
				m->ennemy[x].dead = 1;
		}
		Mix_PlayChannel(6, w->sound.dammage, 0);
	}
}

void		ennemy_go_to(t_map *m, int x, t_coor coor)
{
	double		diffx;
	double		diffy;

	diffx = 0;
	diffy = 0;
	if (m->ennemy[x].coor.x != coor.x || m->ennemy[x].coor.y != coor.y)
	{
		if (m->ennemy[x].range < 1 && m->ennemy[x].dead == 0)
		{
			diffx = coor.x - m->ennemy[x].coor.x;
			diffy = coor.y - m->ennemy[x].coor.y;
		}
		m->ennemy[x].move_speed.x = diffx * 0.005;
		m->ennemy[x].move_speed.y = diffy * 0.005;
		m->ennemy[x].movespeed = 1;
	}
}

void		draw_ennemy(t_env *w, t_map *m, int x, double ratio)
{
	t_cal_sprt	data;
	t_img		img;

	ennemy_go_to(m, x, m->player.coor);
	data = calcul_sprite_ennemy(w, m, x, ratio);
	if (m->player.firing == 1 && m->weap[PH].range * m->ennemy[x].range >= 200)
		hit_box(w, m, x, data);
	if (data.t1z > 0)
	{
		img = fill_t_img(data.x1, data.y1a, m->sprite[m->ennemy[x].index].w
			* data.zoom * ratio, 0);
		sprt_to_screen(w, m->sprite[m->ennemy[x].index], img);
	}
}
