/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:19:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 11:15:52 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cal_sprt	calcul_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	tmp;

	tmp.v1x = m->sprt[x].sx - PL_X;
	tmp.v1y = m->sprt[x].sy - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.diffx = m->player.coor.x - m->sprt[x].sx;
	tmp.diffy = m->player.coor.y - m->sprt[x].sy;
	tmp.zoom = m->sprt[x].range;
	if (m->player.aiming == 1)
		tmp.zoom *= 2;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1 + (m->sprite[m->sprt[x].index].w
		/ 2 * tmp.zoom * ratio));
	if (ft_strcmp(m->sprite[m->sprt[x].index].type, "mur") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor
			- m->player.coor.z + 12), tmp.t1z, m) * tmp.yscale1)
				- (m->sprite[m->sprt[x].index].h * tmp.zoom * ratio);
	else
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1)
				- (m->sprite[m->sprt[x].index].h * tmp.zoom * ratio);
	return (tmp);
}

void		draw_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	d;
	t_img		img;
	int			o;

	o = m->sprt[x].index;
	d = calcul_sprite(w, m, x, ratio);
	if (ft_strcmp(m->sprite[o].type, "rotate") == 0)
		o = rotate(d, o);
	if (ft_strcmp(m->sprite[o].type, "mur") == 0
		&& ((m->elevator == 1 || m->elevator == 2) || m->door == 1))
		o = 25;
	if (d.t1z > 0 && m->sprt[x].vis == 1)
	{
		if (ft_strcmp(m->sprite[o].type, "auto") == 0)
		{
			img = fill_t_img(d.x1, d.y1a, 0, m->sprite[o].h * d.zoom * ratio);
			sprt_to_screen(w, m->sprite[o], img);
		}
		else
		{
			img = fill_t_img(d.x1, d.y1a, m->sprite[o].w * d.zoom * ratio, 0);
			sprt_to_screen(w, m->sprite[o], img);
		}
	}
}

void		sprite_on_ground(t_env *w, t_map *m, double **tab, int x)
{
	if (m->sprt[(int)tab[x][1]].range > 0.7)
		m->sprt[(int)tab[x][1]].vis = 1;
	else if (m->sprt[(int)tab[x][1]].range < 0.1)
		m->sprt[(int)tab[x][1]].vis = 0;
	if (m->sprt[(int)tab[x][1]].taken != 1)
		draw_sprite(w, m, (int)tab[x][1], 1);
	if (m->sprt[(int)tab[x][1]].range >= 2
		&& ft_strcmp(m->sprite[m->sprt[(int)tab[x][1]].index].type, "auto") == 0
		&& m->sprt[(int)tab[x][1]].taken != 1)
	{
		if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\thealth") == 0
			&& m->player.hp < m->player.max_hp)
		{
			m->player.hp += 30;
			m->sprt[(int)tab[x][1]].taken = 1;
		}
		else if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\tcartouche") == 0)
			m->player.bullet[1] += 6;
		else if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\tammo") == 0)
			m->player.bullet[0] += 30;
		else if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\tbadge") == 0)
			m->player.take[3] = 1;
		if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\thealth") != 0)
			m->sprt[(int)tab[x][1]].taken = 1;
	}
}

void		count_sprite(t_env *w, t_map *m)
{
	int		x;

	m->tab = fill_tab_sprite(m);
	m->tab = fill_tab_ennemy(m);
	m->tab = sort_double_tab(m->tab, m->sprite_map_count + m->ennemy_count);
	x = 0;
	while (x < m->sprite_map_count + m->ennemy_count)
	{
		if ((int)m->tab[x][2] == 0)
			sprite_on_ground(w, m, m->tab, x);
		else
			ennemy_animation(w, m, m->tab, x);
		x++;
	}
	m->player.firing = 0;
}
