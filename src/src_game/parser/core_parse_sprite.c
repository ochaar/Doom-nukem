/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:59 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 12:45:33 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				check_i2(int i2, int i3)
{
	i2++;
	if (i2 == 9)
	{
		ft_putendl("\n");
		ft_putnbr(i3);
		ft_putendl("\n");
	}
	return (i2);
}

Uint32			*faster_please(t_map *m, Uint32 *dst, char *src, int len)
{
	int			i;
	int			i2;
	int			i3;
	char		*current;

	i = 0;
	i3 = 0;
	if ((current = (char *)malloc(sizeof(char) * 9)) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error faster_plz"));
	while (i3 < len)
	{
		i2 = 0;
		while (src[i] != ',' && src[i] != '\0')
		{
			current[i2] = src[i];
			i++;
			i2 = check_i2(i2, i3);
		}
		current[i2] = '\0';
		dst[i3] = ft_atoui_base(current, 16);
		i3++;
		i++;
	}
	free(current);
	return (dst);
}

int				parse_weapon_sprite(t_map *m, char *name, char *def, char *pix)
{
	int			i;
	int			wn;
	int			sn;
	char		**tmp;

	i = 0;
	if ((tmp = ft_strsplit(def, ',')) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
	if (check_tab(tmp, 6) != 0)
		return (-1);
	wn = ft_atoi(tmp[0]);
	sn = ft_atoi(tmp[1]);
	m->weap[wn].sprt[sn].name = strdup_check(m->world, name);
	m->weap[wn].sprt[sn].sx = ft_atoi(tmp[2]);
	m->weap[wn].sprt[sn].sy = ft_atoi(tmp[3]);
	m->weap[wn].sprt[sn].w = ft_atoi(tmp[4]);
	m->weap[wn].sprt[sn].h = ft_atoi(tmp[5]);
	i = ft_atoi(tmp[4]) * ft_atoi(tmp[5]);
	m->weap[wn].sprt[sn].len = i;
	if (!(m->weap[wn].sprt[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "weapon"));
	m->weap[wn].sprt[sn].pix = faster_please(m,
		m->weap[wn].sprt[sn].pix, pix, i);
	ft_memreg(tmp);
	return (0);
}

int				parse_sprite_section(t_map *m, char *name, char *def, char *pix)
{
	int			i;
	int			sn;
	char		**tmp;

	i = 0;
	if ((tmp = ft_strsplit(def, ',')) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
	while (tmp[i] != NULL)
		i++;
	if (i != 3)
		return (-1);
	sn = ft_atoi(tmp[0]);
	m->sprite[sn].type = strdup_check(m->world, name);
	m->sprite[sn].w = ft_atoi(tmp[1]);
	m->sprite[sn].h = ft_atoi(tmp[2]);
	i = ft_atoi(tmp[1]) * ft_atoi(tmp[2]);
	m->sprite[sn].len = i;
	process_hint_w(m->world, 1, "sprite");
	if (!(m->sprite[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "sprite"));
	process_hint_w(m->world, 6, name);
	process_hint_w(m->world, 0, " ");
	m->sprite[sn].pix = faster_please(m, m->sprite[sn].pix, pix, i);
	ft_memreg(tmp);
	return (0);
}

void			parse_sprite_line(t_env *w, t_map *m, char *line, t_babytrot *b)
{
	char		**tab;
	int			i;

	i = 0;
	if ((tab = ft_strsplit(line, ':')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	while (tab[i] != NULL)
		i++;
	if (i != 3 && i != 4)
		set_error(w, m, 911, strdup_check(w, PAKOMSA));
	if (ft_strcmp(tab[0], "weapon_sprite") == 0)
	{
		process_hint_w(m->world, 4, "weapon sprite");
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
			set_error(w, m, 8, strdup_check(w, "weapon sprite"));
	}
	if (ft_strcmp(tab[0], "weapon_sprite") != 0)
	{
		if (parse_sprite_section(m, tab[0], tab[1], tab[2]) == -1)
			set_error(w, m, 8, strdup_check(w, "sprites"));
	}
	ft_memreg(tab);
	b->sprite++;
}
