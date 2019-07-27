/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 11:18:57 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 09:55:45 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_free_sector(t_map *m)
{
	int	i;

	i = 0;
	if (m->sector != NULL)
	{
		while (i < m->sector_count && i < m->s)
		{
			if (m->sector[i].dot != NULL)
				free(m->sector[i].dot);
			if (m->sector[i].network != NULL)
				free(m->sector[i].network);
			i++;
		}
		free(m->sector);
		m->sector = NULL;
	}
}
