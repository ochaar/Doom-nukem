/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 12:48:37 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/20 13:44:10 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		face_back(t_cal_sprt data, int o)
{
	if (data.diffy < -5)
		o = 18;
	else
		o = 14;
	return (o);
}

int		rotate(t_cal_sprt data, int o)
{
	if (data.diffx >= 5)
	{
		if (data.diffy >= 5)
			o = 15;
		else if (data.diffy < 5 && data.diffy >= -5)
			o = 16;
		else
			o = 17;
	}
	else if (data.diffx < 5 && data.diffx >= -5)
		o = face_back(data, o);
	else
	{
		if (data.diffy >= 5)
			o = 21;
		else if (data.diffy < 5 && data.diffy >= -5)
			o = 20;
		else
			o = 19;
	}
	return (o);
}

void	test_sprite(t_map *m, double xx, double yy)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		if (m->sprt[x].vis != 1)
		{
			if (m->sprt[x].sx == (int)xx && m->sprt[x].sy == (int)yy
				&& m->sprt[x].vis != 1)
				m->sprt[x].vis = 1;
		}
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		if (m->ennemy[x].vis != 1)
		{
			if ((int)m->ennemy[x].coor.x == (int)xx && (int)m->ennemy[x].coor.y
				== (int)yy && m->ennemy[x].vis != 1)
				m->ennemy[x].vis = 1;
		}
		x++;
	}
}

void	clear_sprite(t_map *m)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		m->sprt[x].vis = 0;
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		m->ennemy[x].vis = 0;
		x++;
	}
}
