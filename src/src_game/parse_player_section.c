/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:37:00 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/21 14:54:12 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			parse_other_info(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tplayer_max_hp") == 0)
		m->player.max_hp = ft_atoi(tab[1]);
	else if (ft_strcmp(tab[0], "\tgravity") == 0)
		m->gravity = ft_atof(tab[1]);
	else if (ft_strcmp(tab[0], "\tgod_mod") == 0)
		m->god_mod = ft_atoi(tab[1]);
	else if (ft_strcmp(tab[0], "Section") != 0)
		return (-1);
	m->player.hp = m->player.max_hp;
	return (0);
}

int			parse_player_section(t_map *m, char **tab)
{
	char	**tmp;

	if (ft_strcmp(tab[0], "\tplayer_location") == 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		if (tmp == NULL)
			return (-1);
		m->player.coor.x = ft_atof(tmp[0]);
		m->player.coor.y = ft_atof(tmp[1]);
		ft_memreg(tmp);
	}
	else if (ft_strcmp(tab[0], "\tplayer_direction") == 0)
	{
		m->player.angle = (ft_atof(tab[1]) * M_PI / 180);
		m->player.anglecos = cos(m->player.angle);
		m->player.anglesin = sin(m->player.angle);
	}
	else if (ft_strcmp(tab[0], "\tplayer_sector") == 0)
	{
		m->player.sector = ft_atoi(tab[1]);
		m->player.coor.z = m->sector[m->player.sector].floor + STAND;
	}
	else if (parse_other_info(m, tab) != 0)
		return (-1);
	return (0);
}
