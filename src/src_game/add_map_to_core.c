/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map_to_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:06:19 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 11:06:49 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	write_set_next_buffer(t_filer *f)
{
	ft_putendl_fd(f->line, f->fd);
	f->buffer = ft_atoi(f->tmp[1]);
	ft_memreg(f->tmp);
	free(f->line);
}

static void	write_new_map(t_map *m, t_filer *f)
{
	while (get_next_line(m->fd, &m->line))
	{
		ft_putendl_fd(m->line, f->fd);
		free(m->line);
	}
	ft_putendl_fd("\nENDMAPSECTION", f->fd);
	free(m->line);
}

static void	read_file(t_env *w, t_map *m, t_filer *f, int i)
{
	while (precise_get_next_line(f->fd2, &f->line, f->buffer))
	{
		if ((f->tmp = ft_strsplit(f->line, ';')) == NULL)
			set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
		process_percent(w, i, 2);
		if (ft_strncmp(f->line, "buffer", 6) == 0)
		{
			write_set_next_buffer(f);
			continue;
		}
		else if (ft_strcmp(f->line, "ENDMAPSECTION") == 0)
			write_new_map(m, f);
		else
			ft_putendl_fd(f->line, f->fd);
		if (ft_strncmp(f->line, "texture\t\t;ascii", 15) != 0
			&& ft_strncmp(f->line, "texture\t\t;main_pic", 18) != 0
				&& ft_strncmp(f->line, "texture\t\t;texturing", 19) != 0)
			f->buffer = 256;
		ft_memreg(f->tmp);
		free(f->line);
		i++;
	}
}

void		add_map_to_core(char *path, char *path2, t_env *w, t_map *m)
{
	t_filer f;
	int		i;

	i = 0;
	f.stop = 0;
	f.buffer = 256;
	if ((f.fd = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, 0655)) != -1
		&& (f.fd2 = open(path, O_RDONLY)) != -1
		&& (m->fd = open(path2, O_RDONLY)) != -1)
	{
		read_file(w, m, &f, i);
		free(f.line);
		close(f.fd2);
		close(f.fd);
		close(m->fd);
	}
	rename("./tmp", path);
}
