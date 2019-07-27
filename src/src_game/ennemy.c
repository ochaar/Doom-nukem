/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:43 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/20 16:26:50 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ennemy_attack(t_map *m, int x)
{
	if (m->ennemy[x].cpt % 2 == 0)
	{
		m->ennemy[x].index = 9;
		m->ennemy[x].die = 1;
	}
	else
	{
		m->ennemy[x].index = 10;
		if (m->ennemy[x].die == 1 && m->god_mod == 0)
		{
			m->player.hp -= 10;
			m->ennemy[x].die = 0;
		}
	}
}

void	ennemy_walk(t_map *m, int x)
{
	if (m->ennemy[x].cpt % 3 == 0)
		m->ennemy[x].index = 6;
	if (m->ennemy[x].cpt % 3 == 1)
		m->ennemy[x].index = 7;
	if (m->ennemy[x].cpt % 3 == 2)
		m->ennemy[x].index = 8;
}

void	swipe_sprite(t_env *w, t_map *m, int x)
{
	if (w->dtime.walk == 0)
		m->ennemy[x].cpt++;
	if (m->ennemy[x].range < 1)
		ennemy_walk(m, x);
	else
		ennemy_attack(m, x);
	if (m->ennemy[x].touche == 1)
	{
		m->ennemy[x].index = 11;
		if (w->dtime.dead == 0)
			m->ennemy[x].count++;
		if (m->ennemy[x].count % 3 == 2)
		{
			m->ennemy[x].touche = 0;
			m->ennemy[x].count = 0;
		}
	}
	draw_ennemy(w, m, x, 1.2);
}

void	ennemy_animation(t_env *w, t_map *m, double **tab, int x)
{
	if (m->ennemy[(int)tab[x][1]].range > 0.5)
		m->ennemy[(int)tab[x][1]].vis = 1;
	if (m->ennemy[(int)tab[x][1]].vis == 1)
	{
		if (m->ennemy[(int)tab[x][1]].dead == 0)
			swipe_sprite(w, m, (int)tab[x][1]);
		else
		{
			if (w->dtime.dead == 0)
				m->ennemy[(int)tab[x][1]].count++;
			if (m->ennemy[(int)tab[x][1]].count % 3 == 0
				&& m->ennemy[(int)tab[x][1]].is_dead == 0)
				m->ennemy[(int)tab[x][1]].index = 11;
			else if (m->ennemy[(int)tab[x][1]].count % 3 == 1
				&& m->ennemy[(int)tab[x][1]].is_dead == 0)
				m->ennemy[(int)tab[x][1]].index = 12;
			else
			{
				m->ennemy[(int)tab[x][1]].index = 13;
				m->ennemy[(int)tab[x][1]].is_dead = 1;
			}
			draw_ennemy(w, m, (int)tab[x][1], 1.2);
		}
	}
}
