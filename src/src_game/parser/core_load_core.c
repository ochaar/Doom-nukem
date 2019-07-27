/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_load_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:08 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 10:44:57 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int			final_verif(t_env *w, t_map *m, t_babytrot babytrotter)
{
	if (w->corenbl == 0
		|| babytrotter.settings == 0
		|| babytrotter.allocs < 4
		|| babytrotter.weapon != m->weapon_count
		|| babytrotter.texture != m->texture_count + w->asciichk + 7
		|| babytrotter.sprite != m->sprite_count + m->weapon_count * 3)
		return (-1);
	else
		return (0);
}

static t_babytrot	init_babytrotter(void)
{
	t_babytrot babytrotter;

	babytrotter.settings = 0;
	babytrotter.allocs = 0;
	babytrotter.weapon = 0;
	babytrotter.texture = 0;
	babytrotter.sprite = 0;
	return (babytrotter);
}

static void			check_vitals(t_env *w, t_map *m, t_babytrot *babytrotter)
{
	char			**tmp;

	if ((tmp = ft_strsplit(m->line, ';')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if (ft_strncmp(m->line, "settings", 8) == 0)
	{
		parse_settings_line(w, m, tmp[1]);
		babytrotter->settings = 1;
	}
	else if (ft_strncmp(m->line, "alloc", 5) == 0)
	{
		parse_allocating_line(w, m, tmp[1]);
		babytrotter->allocs++;
	}
	ft_memreg(tmp);
	w->corenbl++;
}

static void			interpret_line(t_env *w, t_map *m, int *buff, t_babytrot *b)
{
	char			**tmp;

	if ((tmp = ft_strsplit(m->line, ';')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if (ft_strncmp(m->line, "buffer", 6) == 0)
	{
		*buff = ft_atoi(tmp[1]);
		ft_memreg(tmp);
		return ;
	}
	else if (ft_strncmp(m->line, "weapon", 6) == 0)
		parse_weapon_line(m, tmp[1], b);
	else if (ft_strncmp(m->line, "texture", 7) == 0)
		parse_texture_line(w, m, tmp[1], b);
	else if (ft_strncmp(m->line, "sprite", 6) == 0)
		parse_sprite_line(w, m, tmp[1], b);
	if (ft_strncmp(m->line, "texture\t\t;ascii", 15) != 0
		&& ft_strncmp(m->line, "texture\t\t;main_pic", 18) != 0)
		*buff = 128;
	ft_memreg(tmp);
	w->corenbl++;
}

void				load_core(t_env *w, t_map *m)
{
	int				buffer;
	t_babytrot		babytrotter;

	buffer = 128;
	babytrotter = init_babytrotter();
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (precise_get_next_line(m->fd, &m->line, buffer))
		{
			if (babytrotter.settings == 0 || babytrotter.allocs < 4)
				check_vitals(w, m, &babytrotter);
			else
				interpret_line(w, m, &buffer, &babytrotter);
			free(m->line);
		}
		close(m->fd);
		free(m->line);
	}
	else
		set_error(w, m, 5, strdup_check(w, "core/core.dn3d"));
	if (final_verif(w, m, babytrotter) != 0)
		set_error(w, m, 911, strdup_check(w, PAKOMSA));
	w->nbmaps = get_nb_maps_in_core(w);
}
