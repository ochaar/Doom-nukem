/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 01:45:22 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 06:58:46 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		not_a_command(t_env *w, t_map *m, char ***cmd, char *s)
{
	ft_memreg3(cmd);
	set_error(w, m, 2, strdup_check(w, s));
}

void		interpret_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int		ac;
	int		i;

	i = 0;
	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		while (cmd[i] != NULL)
		{
			not_a_command(w, m, cmd, strdup_check(w, cmd[i][0]));
			i++;
		}
	}
	else
		set_error(w, m, 1, strdup_check(w, av[1]));
	ft_memreg3(cmd);
}
