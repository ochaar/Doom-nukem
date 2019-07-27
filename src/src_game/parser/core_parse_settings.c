/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:08:51 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 10:46:46 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			parse_settings_line(t_env *w, t_map *m, char *l)
{
	char		**tmp;

	if (l == NULL)
		set_error(w, m, 911, strdup_check(w, "error on core settings"));
	if ((tmp = ft_strsplit(l, ':')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	check_tab_exit(w, tmp, 5);
	if (w->window_mode == -1)
		w->window_mode = ft_atoi(tmp[0]);
	set_screen_res(w, tmp[1]);
	m->player.field_of_vision_h = ft_atof(tmp[2]) * WIDTH / BASEWIDTH;
	m->player.field_of_vision_v = ft_atof(tmp[3]) * HEIGHT / BASEHEIGHT;
	w->mem_field_of_vision_h = m->player.field_of_vision_h;
	w->mem_field_of_vision_v = m->player.field_of_vision_v;
	m->player.mousesp = ft_atof(tmp[4]);
	ft_memreg(tmp);
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, strdup_check(w, "SDL Initialisation"));
}
