/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_nb_names.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:50:29 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 07:09:31 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			loop_nb_maps(t_env *w)
{
	int		nbmaps;
	char	**tmp;

	nbmaps = 0;
	while (get_next_line_until(w->m->fd, &w->m->line, WSR) && WSR == 0)
	{
		if ((tmp = ft_strsplit(w->m->line, ';')) == NULL)
			set_error(w, w->m, 0, strdup_check(w, "str_split maps"));
		if (ft_strncmp(w->m->line, "map\t\t\t", 6) == 0)
		{
			if (tmp[1] != NULL && ft_strisnone(tmp[1]) != 1)
				nbmaps++;
		}
		else if (ft_strncmp(w->m->line, "ENDMAPSECTION", 13) == 0)
			WSR = 1;
		ft_memreg(tmp);
		free(w->m->line);
	}
	return (nbmaps);
}

int			get_nb_maps_in_core(t_env *w)
{
	int		nbmaps;

	nbmaps = 0;
	WSR = 0;
	if ((w->m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		nbmaps = loop_nb_maps(w);
		free(w->m->line);
		close(w->m->fd);
	}
	else
		set_error(w, w->m, 5, strdup_check(w, "core/core.dn3d"));
	return (nbmaps);
}

void		loop_names_map(t_env *w, t_map *m, char **names)
{
	char **tmp;

	while (get_next_line_until(m->fd, &m->line, WSR) && WSR == 0)
	{
		if ((tmp = ft_strsplit(w->m->line, ';')) == NULL)
			set_error(w, w->m, 0, strdup_check(w, "str_split maps"));
		if (ft_strcmp(tmp[0], "map\t\t\t") == 0)
		{
			if (tmp[1] != NULL && ft_strisnone(tmp[1]) != 1)
			{
				names[w->i] = strdup_check(w, tmp[1]);
				w->i++;
			}
		}
		else if (ft_strcmp(m->line, "ENDMAPSECTION") == 0)
			WSR = 1;
		ft_memreg(tmp);
		free(m->line);
	}
}

int			get_names_maps_in_core(t_env *w, t_map *m, char **names)
{
	w->i = 0;
	WSR = 0;
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		loop_names_map(w, m, names);
		free(m->line);
		close(m->fd);
	}
	else
		set_error(w, w->m, 5, strdup_check(w, "core/core.dn3d"));
	return (0);
}
