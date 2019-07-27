/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:34 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 10:55:12 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				parse_level_map(t_map *m, char **tab)
{
	char		**tmp;

	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL)
	{
		if ((tmp = ft_strsplit(tab[1], ',')) == NULL)
			set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
		m->endsector = ft_atoi(tmp[0]);
		m->linklvl = strdup_check(m->world, tmp[1]);
		ft_memreg(tmp);
	}
	return (0);
}

int				second_parse(t_env *w, t_map *m, char **tmp)
{
	if (m->section_number == 2)
	{
		if (parse_player_section(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 3)
	{
		if (parse_sprite_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 4)
	{
		if (parse_ennemy_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 5)
	{
		if (parse_level_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 6)
		w->stopread = 1;
	return (0);
}

int				parse_map_section(t_map *m, char **tab)
{
	int			check;

	check = ft_tab_len(tab);
	if (ft_strcmp(tab[0], "\tdots") == 0)
	{
		if (parse_map_dots(m, tab) == -1)
		{
			ft_putendl("error on parsing of the dot section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "\tsector") == 0)
	{
		if (parse_sectors(m, tab, check) == -1)
		{
			ft_putendl("error on parsing of the \"sector\" section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "Section") != 0)
		return (-1);
	return (0);
}

int				parse_map_line(t_env *w, t_map *m)
{
	char		**tmp;

	if ((tmp = ft_strsplit(m->line, ':')) == NULL)
		return (-1);
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 0)
	{
		if (parse_first_line(m) == -1)
			return (-1);
	}
	else if (m->section_number == 1)
	{
		process_hint_w(w, 4, "map");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	else if (second_parse(w, m, tmp) == -1)
		return (-1);
	ft_memreg(tmp);
	return (0);
}
