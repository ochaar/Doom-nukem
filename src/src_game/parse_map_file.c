/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:27:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/17 11:18:09 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_map_structs(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->sprite_map_count)
	{
		m->sprt[i].name = NULL;
		i++;
	}
}

int		second_parse(t_env *w, t_map *m, char **tmp)
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

int		parse_line(t_env *w, t_map *m)
{
	char	**tmp;

	if ((tmp = ft_strsplit(m->line, ':')) == NULL)
		return (-1);
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 0)
	{
		if (first_line(m) == -1)
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
