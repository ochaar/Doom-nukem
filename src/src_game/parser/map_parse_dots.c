/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_dots.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:38 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 10:52:55 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			parse_map_dots(t_map *m, char **tab)
{
	int		i;
	char	**tmp;

	i = 0;
	if (check_tab(tab, 3) != 0)
		return (-1);
	tmp = ft_strsplit(tab[2], ',');
	while (tmp[i] != NULL)
	{
		if (m->i < m->dots_count)
		{
			m->dot[m->i].x = ft_atof(tmp[i]);
			m->dot[m->i].y = ft_atof(tab[1]);
		}
		i++;
		m->i++;
		m->dotsc++;
	}
	if (m->i > m->dots_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}
