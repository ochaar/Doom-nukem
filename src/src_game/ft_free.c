/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:18:57 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/15 13:11:03 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_free_tab(t_map *m)
{
	int		i;

	i = 0;
	if (m->tab != NULL)
	{
		while (i < m->sprite_map_count + m->ennemy_count)
		{
			free(m->tab[i]);
			i++;
		}
		free(m->tab);
		m->tab = NULL;
	}
}

void		ft_free_sprt(t_map *m)
{
	m->i = 0;
	if (m->sprt != NULL)
	{
		while (m->i < m->sprite_map_count)
		{
			free(m->sprt[m->i].name);
			m->i++;
		}
		free(m->sprt);
		m->sprt = NULL;
	}
}

void		ft_free_sprite(t_map *m)
{
	m->i = 0;
	if (m->sprite != NULL)
	{
		while (m->i < m->sprite_count)
		{
			free(m->sprite[m->i].type);
			free(m->sprite[m->i].pix);
			m->i++;
		}
		free(m->sprite);
		m->sprite = NULL;
	}
	ft_free_tab(m);
	ft_free_sprt(m);
	if (m->fire.pix != NULL)
	{
		free(m->fire.pix);
		m->fire.pix = NULL;
	}
}

void		ft_free_weap(t_map *m)
{
	int	i;

	i = 0;
	if (m->weap != NULL)
	{
		while (i < m->weapon_count)
		{
			if (m->weap[i].shoot != NULL)
				Mix_FreeChunk(m->weap[i].shoot);
			free(m->weap[i].sprt[0].pix);
			free(m->weap[i].sprt[0].name);
			free(m->weap[i].sprt[1].pix);
			free(m->weap[i].sprt[1].name);
			free(m->weap[i].sprt[2].pix);
			free(m->weap[i].sprt[2].name);
			free(m->weap[i].name);
			i++;
		}
		free(m->weap);
		m->weap = NULL;
	}
}
