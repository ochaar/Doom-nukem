/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_allocations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:46 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 12:22:36 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			init_weapon_struct(t_map *m)
{
	int			i;

	i = 0;
	while (i < m->weapon_count)
	{
		m->weap[i].name = NULL;
		m->weap[i].shoot = NULL;
		m->weap[i].sprt[0].pix = NULL;
		m->weap[i].sprt[0].name = NULL;
		m->weap[i].sprt[1].pix = NULL;
		m->weap[i].sprt[1].name = NULL;
		m->weap[i].sprt[2].pix = NULL;
		m->weap[i].sprt[2].name = NULL;
		i++;
	}
}

void			do_alloc(t_env *w, t_map *m)
{
	if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon)
		* m->weapon_count)) == NULL)
		set_error(w, m, 0, strdup_check(w, "weapon"));
	init_weapon_struct(m);
	if (load_sounds(w, m) == -1)
		set_error(w, m, 8, strdup_check(w, "load_sounds"));
	if ((w->ascii = (t_texture *)malloc(sizeof(t_texture)
		* w->asciino)) == NULL)
		set_error(w, m, 0, strdup_check(w, "ascii"));
	if ((m->sprite = (t_sprite *)malloc(sizeof(t_sprite)
		* m->sprite_count)) == NULL)
		set_error(w, m, 0, strdup_check(w, "sprite"));
	if ((w->texturing = (t_texture *)malloc(sizeof(t_texture)
		* m->texture_count)) == NULL)
		set_error(w, m, 0, strdup_check(w, "texturing"));
}

void			parse_allocating_line(t_env *w, t_map *m, char *line)
{
	char		**tmp;

	if (line == NULL)
		set_error(m->world, m, 911, strdup_check(w, "weapon line"));
	if ((tmp = ft_strsplit(line, ':')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	check_tab_exit(w, tmp, 2);
	if (ft_strcmp(tmp[0], "weapon") == 0)
		m->weapon_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "ascii") == 0)
		w->asciino = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "sprite") == 0)
		m->sprite_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "texturing") == 0)
		m->texture_count = ft_atoi(tmp[1]);
	if (w->asciino > 0 && m->weapon_count > 0
		&& m->sprite_count > 0 && m->texture_count > 0)
		do_alloc(w, m);
	ft_memreg(tmp);
}
