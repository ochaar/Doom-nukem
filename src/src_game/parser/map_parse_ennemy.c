/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_ennemy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:47 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 16:41:10 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		set_ennemy(t_map *m, int nb)
{
	m->ennemy[nb].range = 0.5;
	m->ennemy[nb].dead = 0;
	m->ennemy[nb].is_dead = 0;
	m->ennemy[nb].die = 1;
	m->ennemy[nb].count = 0;
	m->ennemy[nb].cpt = 0;
	m->ennemy[nb].nb_ammo = 0;
	m->ennemy[nb].touche = 0;
	m->ennemy[nb].move_speed.x = 0;
	m->ennemy[nb].move_speed.y = 0;
	m->ennemy[nb].move_speed.z = 0;
	m->ennemy[nb].move_speedless.x = 0;
	m->ennemy[nb].move_speedless.y = 0;
	m->ennemy[nb].move_speedless.z = 0;
	return (0);
}

void	fill_ennemy(t_map *m, t_ennemy *ennemy, char **tmp)
{
	ennemy->index = ft_atoi(tmp[1]);
	ennemy->sector = ft_atoi(tmp[2]);
	ennemy->coor.x = ft_atof(tmp[3]);
	ennemy->coor.y = ft_atof(tmp[4]);
	if (ennemy->sector < m->sector_count && ennemy->sector >= 0)
		ennemy->coor.z = m->sector[ennemy->sector].floor + STAND;
	ennemy->fall = 1;
	ennemy->ground = 0;
	ennemy->moving = 0;
	ennemy->height = 0;
	ennemy->hole_low = 0;
	ennemy->hole_high = 0;
}

int		parse_ennemy_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	int		check;

	check = 0;
	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL && m->ennemyc < m->ennemy_count)
	{
		if ((tmp = ft_strsplit(tab[1], ',')) == NULL)
			set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
		check = ft_tab_len(tmp);
		if (check == 5)
		{
			nb = ft_atoi(tmp[0]);
			fill_ennemy(m, &m->ennemy[nb], tmp);
			set_ennemy(m, nb);
			m->ennemyc++;
		}
		ft_memreg(tmp);
	}
	return (0);
}
