/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:19:31 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 14:02:46 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			init_world(t_env **w, t_map **m, int ac)
{
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		exit(0);
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
	{
		free(w);
		exit(0);
	}
	set_basics(*w, *m, ac);
}

void			set_basics(t_env *w, t_map *m, int ac)
{
	w->m = m;
	m->world = w;
	set_w(w, ac);
	set_m(m);
	set_m_player(m);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;

	w = NULL;
	m = NULL;
	cmd = NULL;
	init_world(&w, &m, ac);
	if (ac > 1)
		interpret_cmd(w, m, cmd, av);
	load_core(w, m);
	launch(w, m);
	exit_game(w, m, 0);
	return (0);
}
