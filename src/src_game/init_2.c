/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:14:54 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 07:22:59 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_sprite_tab(t_map *m)
{
	int i;

	i = 0;
	if (!(m->tab = (double**)malloc(sizeof(double*) * (m->sprite_map_count
		+ m->ennemy_count))))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "m->tab"));
	while (i < m->sprite_map_count + m->ennemy_count)
	{
		if (!(m->tab[i] = (double*)malloc(sizeof(double) * 3)))
			set_error((t_env *)m->world, m, 0,
				strdup_check(m->world, "m->tab[i]"));
		i++;
	}
}

void		init_map_structs(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->sprite_map_count)
	{
		m->sprt[i].name = NULL;
		i++;
	}
}

t_texture	pre_init_texture(int w, int h)
{
	t_texture		texture;

	if (w > 0 && h > 0)
	{
		texture.w = w;
		texture.h = h;
		texture.len = w * h;
		texture.pix = (Uint32 *)malloc(sizeof(Uint32) * w * h);
	}
	else
	{
		texture.w = 0;
		texture.h = 0;
		texture.len = 0;
		texture.pix = NULL;
	}
	return (texture);
}
