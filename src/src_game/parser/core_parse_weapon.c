/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_weapon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:26 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 12:20:33 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				fill_arg(int *nb, char *number)
{
	int			i;

	i = 0;
	while (number[i] != '\0')
	{
		if (ft_isdigit((int)number[i]) != 1)
			return (-1);
		i++;
	}
	i = ft_atoi(number);
	*nb = i;
	return (0);
}

void			fill_weapon_int(t_map *m, char **tmp)
{
	int			i;

	i = 0;
	while (tmp[i] != NULL)
	{
		if (i == 0 && fill_arg(&m->weap[m->w].range, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		if (i == 1 && fill_arg(&m->weap[m->w].firerate, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		if (i == 2 && fill_arg(&m->weap[m->w].accuracy, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		if (i == 4 && fill_arg(&m->weap[m->w].ammo_type, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		if (i == 5 && fill_arg(&m->weap[m->w].magazine, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		if (i == 6 && fill_arg(&m->weap[m->w].recoil, tmp[i]) != 0)
			set_error(m->world, m, 911, strdup_check(m->world, "weapon line"));
		i++;
	}
}

void			parse_weapon_line(t_map *m, char *line, t_babytrot *b)
{
	char		**tmp;
	char		**tmp2;

	if ((tmp2 = ft_strsplit(line, ':')) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
	check_tab_exit(m->world, tmp2, 3);
	m->weap[m->w].name = strdup_check(m->world, tmp2[0]);
	if ((tmp = ft_strsplit(tmp2[1], ',')) == NULL)
		set_error(m->world, m, 0, strdup_check(m->world, "error strsplit"));
	check_tab_exit(m->world, tmp, 7);
	m->weap[m->w].reloadtime = ft_atof(tmp2[2]);
	m->weap[m->w].dispertion = ft_atof(tmp[3]);
	fill_weapon_int(m, tmp);
	ft_memreg(tmp2);
	ft_memreg(tmp);
	m->w++;
	b->weapon++;
}
