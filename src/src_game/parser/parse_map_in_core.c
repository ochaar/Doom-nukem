/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_in_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:30 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 11:07:15 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				get_that_map_parsed(t_env *w, t_map *m)
{
	free(m->line);
	set_count(m);
	m->section_number = 0;
	process_hint_w(w, 6, "map");
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
	while (get_next_line_until(m->fd, &m->line, WSR) && WSR == 0)
	{
		if ((parse_map_line(w, m)) == -1)
		{
			write(2, "error on map collect\n", 22);
			free(m->line);
			return (-1);
		}
		free(m->line);
	}
	free(m->line);
	process_hint_w(w, 0, " ");
	if (m->dotsc != m->dots_count || m->s != m->sector_count
		|| m->spmc != m->sprite_map_count || m->ennemyc != m->ennemy_count)
		return (-1);
	return (0);
}

static void		parse_failed(t_env *w)
{
	w->menu.i = 1;
	WSR = 1;
	w->m->newgame = 1;
}

static char		*pre_loading(t_env *w, t_map *m, char *name)
{
	char		*tmp;
	char		*pre;

	pre = strdup_check(w, "map\t\t\t;");
	if ((tmp = ft_strjoin(pre, name)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	free(pre);
	WSR = 0;
	reset_map(m);
	reset_player(w, m);
	return (tmp);
}

static int		process_line(t_env *w, t_map *m, char *tmp)
{
	if (ft_strcmp(m->line, tmp) == 0)
	{
		if (get_that_map_parsed(w, m) != 0)
		{
			parse_failed(w);
			get_next_line_until(m->fd, &m->line, WSR);
			free(m->line);
			return (-1);
		}
	}
	else if (ft_strcmp(m->line, "ENDMAPSECTION") == 0)
	{
		parse_failed(w);
		free(m->line);
		return (1);
	}
	else
		free(m->line);
	return (0);
}

int				parse_map_in_core(t_env *w, t_map *m, char *name)
{
	char		*tmp;
	int			state;

	tmp = pre_loading(w, m, name);
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(m->fd, &m->line, WSR) && WSR == 0)
		{
			if ((state = process_line(w, m, tmp)) != 0)
			{
				if (state == -1)
					return (-1);
				else
					continue;
			}
		}
		free(m->line);
		close(m->fd);
	}
	else
		set_error(w, m, 5, strdup_check(w, "core/core.dn3d"));
	free(tmp);
	return (0);
}
