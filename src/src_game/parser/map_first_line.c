/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_first_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:53:23 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 10:52:16 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		first_line_compare(t_map *m, char **tmp)
{
	if (ft_strcmp(tmp[0], "dots") == 0
		&& fill_arg(&m->dots_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "sector") == 0
		&& fill_arg(&m->sector_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "sprite") == 0
		&& fill_arg(&m->sprite_map_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "ennemy") == 0
		&& fill_arg(&m->ennemy_count, tmp[1]) == 0)
		return (0);
	else
		return (-1);
}

int		first_line_prepare(t_map *m, char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	while (i < 4)
	{
		if ((tmp = ft_strsplit(tab[i], ':')) == NULL)
			set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
		if (check_tab(tmp, 2) != 0)
			return (-1);
		if (first_line_compare(m, tmp) != 0)
		{
			ft_memreg(tmp);
			return (-1);
		}
		ft_memreg(tmp);
		i++;
	}
	return (0);
}

int		first_line_check(t_map *m)
{
	char	**tmp;
	int		check;

	if ((tmp = ft_strsplit(m->line, ',')) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
	check = ft_tab_len(tmp);
	if (check != 4)
	{
		ft_memreg(tmp);
		return (-1);
	}
	else
	{
		if (first_line_prepare(m, tmp) != 0)
		{
			ft_memreg(tmp);
			return (-1);
		}
	}
	ft_memreg(tmp);
	return (0);
}

int		parse_first_line(t_map *m)
{
	if (first_line_check(m) != 0)
		return (-1);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->sprt = (t_map_sprite *)malloc(sizeof(t_map_sprite)
		* m->sprite_map_count)) == NULL)
		return (-1);
	if ((m->ennemy = (t_ennemy *)malloc(sizeof(t_ennemy) * m->ennemy_count))
		== NULL)
		return (-1);
	init_map_structs(m);
	init_sprite_tab(m);
	return (0);
}
