/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:06:19 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 11:06:49 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		process_percent(t_env *w, int i, int type)
{
	int		nb;

	nb = 0;
	if (w->corenbl != 0)
		nb = vmin(((double)i / (double)(w->corenbl) * (double)100), 99);
	if (type == 1)
		process_hint_w(w, 8, ft_itoa(nb));
	if (type == 2)
		process_hint_savemap(w, 2, w->nbmaps, ft_itoa(nb));
}

int			test_replace_line(t_filer *f, char *balise, char *content)
{
	if (ft_strncmp(f->line, "buffer", 6) == 0)
	{
		ft_putendl_fd(f->line, f->fd);
		f->buffer = ft_atoi(f->tmp[1]);
		ft_memreg(f->tmp);
		free(f->line);
		return (-1);
	}
	else if (ft_strncmp(f->line, balise, ft_strlen(balise)) == 0)
	{
		ft_putstr_fd(balise, f->fd);
		if (ft_strlen(balise) < 8)
			ft_putstr_fd("\t\t;", f->fd);
		else
			ft_putstr_fd("\t;", f->fd);
		ft_putendl_fd(content, f->fd);
	}
	else
		ft_putendl_fd(f->line, f->fd);
	if (ft_strncmp(f->line, "texture\t\t;ascii", 15) != 0
		&& ft_strncmp(f->line, "texture\t\t;main_pic", 18) != 0
			&& ft_strncmp(f->line, "texture\t\t;texturing", 19) != 0)
		f->buffer = 256;
	return (0);
}

void		replace_line(char *path, char *balise, char *content, t_env *w)
{
	t_filer f;
	int		i;

	i = 0;
	f.stop = 0;
	f.buffer = 256;
	if ((f.fd = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, 0655)) != -1
		&& (f.fd2 = open(path, O_RDONLY)) != -1)
	{
		while (precise_get_next_line(f.fd2, &f.line, f.buffer))
		{
			if ((f.tmp = ft_strsplit(f.line, ';')) == NULL)
				set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
			process_percent(w, i, 1);
			if (test_replace_line(&f, balise, content) == -1)
				continue;
			ft_memreg(f.tmp);
			free(f.line);
			i++;
		}
		free(f.line);
		close(f.fd2);
		close(f.fd);
	}
	rename("./tmp", path);
}

static void	change_settings_next(t_env *w, char **nb, char **tmp, char **str)
{
	if ((*nb = ft_itoa(w->m->player.field_of_vision_v)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((*str = ft_strjoinnfree(*tmp, ":", 1)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((*tmp = ft_strjoinnfree(*str, *nb, 3)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((*nb = ft_itoa(w->m->player.mousesp)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((*str = ft_strjoinnfree(*tmp, ":", 1)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((*tmp = ft_strjoinnfree(*str, *nb, 3)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
}

void		change_settings(t_env *w, t_map *m)
{
	char	*nb;
	char	*tmp;
	char	*str;

	if ((nb = ft_itoa(w->window_mode)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((str = ft_strjoinnfree(nb, ":", 1)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((nb = ft_itoa(w->window_res)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((tmp = ft_strjoinnfree(str, nb, 3)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((nb = ft_itoa(m->player.field_of_vision_h)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((str = ft_strjoinnfree(tmp, ":", 1)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	if ((tmp = ft_strjoinnfree(str, nb, 3)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	change_settings_next(w, &nb, &tmp, &str);
	replace_line("./core/core.dn3d", "settings", tmp, w);
	free(tmp);
}
