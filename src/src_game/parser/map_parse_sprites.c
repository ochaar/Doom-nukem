/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:53 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 12:19:41 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_sprite(t_map_sprite *sprite, char **tmp)
{
	sprite->index = ft_atoi(tmp[1]);
	sprite->sector = ft_atoi(tmp[2]);
	sprite->sx = ft_atof(tmp[3]);
	sprite->sy = ft_atof(tmp[4]);
	sprite->vis = 1;
	sprite->taken = 0;
	sprite->range = 0.5;
}

int		parse_sprite_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	int		check;

	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL && m->spmc < m->sprite_map_count)
	{
		if ((tmp = ft_strsplit(tab[1], ',')) == NULL)
			set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
		check = ft_tab_len(tmp);
		if (check == 5)
		{
			nb = ft_atoi(tmp[0]);
			fill_sprite(&m->sprt[nb], tmp);
			m->sprt[nb].name = strdup_check(m->world, tab[0]);
			m->spmc++;
		}
		else
			return (-1);
		ft_memreg(tmp);
	}
	return (0);
}
