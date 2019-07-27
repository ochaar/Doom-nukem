/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevadoor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:56:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 14:58:24 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	elevator(t_map *m)
{
	if (m->elevator == 1)
	{
		m->sector[m->nb_a].floor -= 0.1;
		m->sector[m->nb_a].ceiling -= 0.1;
		if ((int)m->sector[m->nb_a].floor == m->sector[m->nb_a + 1].floor - 1)
			m->elevator = -1;
	}
	else if (m->elevator == 2)
	{
		m->sector[m->nb_a].floor += 0.1;
		m->sector[m->nb_a].ceiling += 0.1;
		if ((int)m->sector[m->nb_a].floor == m->sector[m->nb_a - 1].floor)
			m->elevator = 0;
	}
}
