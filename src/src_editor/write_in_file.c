/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:45:27 by abechet           #+#    #+#             */
/*   Updated: 2019/07/19 01:13:12 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_ennemy(t_win *win, int fp, t_lstast *tmp, int i)
{
	char	*str;

	if (win->lstast)
	{
		str = "\tmonstre:";
		ft_putstr_fd(str, fp);
	}
	ft_light_itoa(i, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",6,";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->sector, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->x / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	ft_light_itoa(tmp->y / 2, win->itoastr);
	ft_putstr_fd(win->itoastr, fp);
}

void		write_ennemies(t_win *win, int fp)
{
	t_lstast	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstast;
	str = "Section:ennemy\n";
	ft_putstr_fd(str, fp);
	while (tmp)
	{
		if (tmp->asset_type == 3)
		{
			write_ennemy(win, fp, tmp, i);
			str = "\n";
			ft_putstr_fd(str, fp);
			i++;
		}
		tmp = tmp->next;
	}
}

void		write_map_mame(t_env *w, int fp)
{
	ft_putstr_fd("map\t\t\t;map", fp);
	w->nbmaps++;
	ft_putnbr_fd(w->nbmaps, fp);
	ft_putchar_fd('\n', fp);
}

void		write_in_file_helper(t_env *w, t_win *win, int fp)
{
	int			boole;

	boole = 0;
	write_map_mame(w, fp);
	process_hint_savemap(w, 1, w->nbmaps, "map");
	first_line2(w, win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "dots");
	write_dots(w, win, fp, boole);
	process_hint_savemap(w, 1, w->nbmaps, "sectors");
	write_sectors(w, win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "player");
	write_player(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "sprites");
	write_sprites(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "ennemies");
	write_ennemies(win, fp);
}

void		write_in_file(t_env *w, t_win *win)
{
	int			fp;
	char		*name;
	char		*str;

	name = strdup_safe(w, win, "tmp.dn3d");
	fp = open(name, O_RDWR | O_CREAT | O_TRUNC, 0655);
	free(name);
	write_in_file_helper(w, win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "sections");
	str = strdup_safe(w, win, "Section:level\n");
	ft_putstr_fd(str, fp);
	free(str);
	str = strdup_safe(w, win, "Section:over\n");
	ft_putstr_fd(str, fp);
	free(str);
	close(fp);
	add_map_to_core("./core/core.dn3d", "./tmp.dn3d", w, w->m);
	unlink("./tmp.dn3d");
}
