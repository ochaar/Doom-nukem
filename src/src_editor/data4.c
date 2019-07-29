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

void		write_ennemy(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tmonstre:";
		ft_putstr_fd(str, fp);
	}
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",6,";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);
	str = ",";
	ft_putstr_fd(str, fp);
	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_ennemies(t_win *win, int fp)
{
	t_lstasset	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstasset;
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

void		write_in_file_helper(t_win *win, t_env *w, int fp)
{
	write_map_mame(w, fp);
	process_hint_savemap(w, 1, w->nbmaps, "map");
	first_line2(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "dots");
	write_dots(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "sectors");
	write_sectors(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "player");
	write_player(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "sprites");
	write_sprites(win, fp);
	process_hint_savemap(w, 1, w->nbmaps, "ennemies");
	write_ennemies(win, fp);
}

void		do_system_to_save(char *name)
{
	char	*command;

	command = ft_strjoinnfree("cat ", name, 2);
	command = ft_strjoinnfree(command, " >> nouveau.txt && echo '\n\n' >> nouveau.txt && cat ./core/core.dn3d >> nouveau.txt", 1);
	system(command);
	free(command);
	system("rm ./core/core.dn3d && rm ./tmp.dn3d && cp ./nouveau.txt ./core && mv ./core/nouveau.txt ./core/core.dn3d && rm ./nouveau.txt");
}

void		write_in_file(t_win *win, t_env *w)
{
	int			fp;
	char	*name;
	char		*str;

	name = ft_strdup("tmp.dn3d");
	fp = open(name, O_RDWR | O_CREAT | O_TRUNC, 0655);
	write_in_file_helper(win, w, fp);
	process_hint_savemap(w, 1, w->nbmaps, "sections");
	str = ft_strdup("Section:level\n");
	ft_putstr_fd(str, fp);
	free(str);
	str = ft_strdup("Section:over\n");
	ft_putstr_fd(str, fp);
	free(str);
	close(fp);

	//do_system_to_save(name);
	add_map_to_core("./core/core.dn3d", "./tmp.dn3d", w);

	unlink("./tmp.dn3d");
}
