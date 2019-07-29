/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:25:09 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/15 13:31:05 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		check_i2(int i2, int i3)
{
	if (i2 == 9)
	{
		ft_putendl("\n");
		ft_putnbr(i3);
		ft_putendl("\n");
	}
}

Uint32		*faster_please(Uint32 *dst, char *src, int len)
{
	int				i;
	int				i2;
	int				i3;
	char			*current;

	i = 0;
	i3 = 0;
	current = (char *)malloc(sizeof(char) * 9);
	while (i3 < len)
	{
		i2 = 0;
		while (src[i] != ',' && src[i] != '\0')
		{
			current[i2] = src[i];
			i++;
			i2++;
			check_i2(i2, i3);
		}
		current[i2] = '\0';
		dst[i3] = ft_atoui_base(current, 16);
		i3++;
		i++;
	}
	free(current);
	return (dst);
}

int			parse_weapon_sprite(t_map *m, char *name, char *def, char *pix)
{
	int				i;
	int				wn;
	int				sn;
	char			**tmp;

	tmp = ft_strsplit(def, ',');
	wn = ft_atoi(tmp[0]);
	sn = ft_atoi(tmp[1]);
	m->weap[wn].sprt[sn].name = ft_strdup(name);
	m->weap[wn].sprt[sn].sx = ft_atoi(tmp[2]);
	m->weap[wn].sprt[sn].sy = ft_atoi(tmp[3]);
	m->weap[wn].sprt[sn].w = ft_atoi(tmp[4]);
	m->weap[wn].sprt[sn].h = ft_atoi(tmp[5]);
	i = ft_atoi(tmp[4]) * ft_atoi(tmp[5]);
	m->weap[wn].sprt[sn].len = i;
	process_hint_w(m->world, 1, "textures");
	m->weap[wn].sprt[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i);
	process_hint_w(m->world, 6, name);
	process_hint_w(m->world, 0, " ");
	m->weap[wn].sprt[sn].pix = faster_please(m->weap[wn].sprt[sn].pix, pix, i);
	process_hint_w(m->world, 0, " ");
	ft_memreg(tmp);
	return (0);
}

int			parse_sprite_section(t_map *m, char *name, char *def, char *pix)
{
	int				i;
	int				sn;
	char			**tmp;

	tmp = ft_strsplit(def, ',');
	sn = ft_atoi(tmp[0]);
	m->sprite[sn].type = ft_strdup(name);
	m->sprite[sn].w = ft_atoi(tmp[1]);
	m->sprite[sn].h = ft_atoi(tmp[2]);
	i = ft_atoi(tmp[1]) * ft_atoi(tmp[2]);
	m->sprite[sn].len = i;
	process_hint_w(m->world, 1, "sprite");
	m->sprite[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i);
	process_hint_w(m->world, 6, name);
	process_hint_w(m->world, 0, " ");
	m->sprite[sn].pix = faster_please(m->sprite[sn].pix, pix, i);
	process_hint_w(m->world, 0, " ");
	ft_memreg(tmp);
	return (0);
}
