/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parse_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:17 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 20:20:55 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_texture		parse_texture(t_env *w, t_map *m, char **tmp)
{
	t_texture	texture;
	char		**tmp2;
	int			i;

	if ((tmp2 = ft_strsplit(tmp[1], ',')) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	i = ft_tab_len(tmp2);
	if (i != 2 && i != 3)
		set_error(w, m, 911, strdup_check(w, PAKOMSA));
	texture.w = ft_atoi(tmp2[0]);
	texture.h = ft_atoi(tmp2[1]);
	texture.len = texture.w * texture.h;
	if ((texture.pix = (Uint32 *)malloc(sizeof(Uint32) * texture.len)) == NULL)
		set_error(w, m, 0, strdup_check(w, "pixels"));
	texture.pix = faster_please(m, texture.pix, tmp[2], texture.len);
	if (tmp2[2] != NULL)
		texture.trsp = ft_atoi(tmp2[2]);
	else
		texture.trsp = 0;
	ft_memreg(tmp2);
	return (texture);
}

static void		parse_texture_next(t_env *w, t_map *m, char **tmp)
{
	if (ft_strcmp(tmp[0], "main_pic[1]") == 0)
		w->main_pic[1] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "main_pic[2]") == 0)
		w->main_pic[2] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud") == 0)
		m->hud = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud2") == 0)
		m->hud2 = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "fire") == 0)
		m->fire = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "blackbox") == 0)
		m->whitebox = parse_texture(w, m, tmp);
}

static void		parse_main_texture(t_env *w, t_map *m, char **tmp)
{
	if (ft_strcmp(tmp[0], "ascii") == 0)
	{
		w->ascii[w->asciichk] = parse_texture(w, m, tmp);
		w->asciichk++;
	}
	if (ft_strcmp(tmp[0], "texturing") == 0)
	{
		w->texturing[w->texturingno] = parse_texture(w, m, tmp);
		w->texturingno++;
	}
	if (ft_strcmp(tmp[0], "main_pic[0]") == 0)
	{
		w->main_pic[0] = parse_texture(w, m, tmp);
		main_pic(w, 0);
		type_str(w, w->txthead, "loading game...", 0x12FEA800);
		img_update(w);
	}
}

void			parse_texture_line(t_env *w, t_map *m, char *l, t_babytrot *b)
{
	char		**tmp;

	w->txthead = fill_t_dot(800, 550);
	process_hint_w(w, 7, "texture");
	if (l == NULL)
		set_error(w, m, 911, strdup_check(w, PAKOMSA));
	tmp = ft_strsplit(l, ':');
	check_tab_exit(w, tmp, 3);
	parse_main_texture(w, m, tmp);
	parse_texture_next(w, m, tmp);
	process_hint_w(w, 0, " ");
	ft_memreg(tmp);
	b->texture++;
}
