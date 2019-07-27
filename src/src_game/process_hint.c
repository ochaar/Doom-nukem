/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:35:38 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 17:38:07 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char			*other_if(int i, char *post)
{
	if (i == 0)
		return (ft_strjoin("done", post));
	else if (i == 1)
		return (ft_strjoin("allocating memory for ", post));
	else if (i == 2)
		return (ft_strjoin("initialisating ", post));
	else if (i == 3)
		return (ft_strjoin("processing ", post));
	else if (i == 4)
		return (ft_strjoin("parsing ", post));
	else if (i == 5)
		return (ft_strjoin("running ", post));
	else if (i == 6)
		return (ft_strjoin("loading ", post));
	else if (i == 7)
		return (ft_strjoin("extracting ", post));
	else if (i == 8)
		return (ft_strjoin("writing ... ", post));
	return (NULL);
}

void			process_hint_w(t_env *w, int i, char *s)
{
	char		*pre;
	char		*post;
	t_dot		dot;

	pre = NULL;
	w->txthead = fill_t_dot(6, 550);
	dot = fill_t_dot(800, 550);
	if (i == 8)
		s = ft_strjoinnfree(s, " %", 1);
	post = ft_strjoin(s, "\r");
	pre = other_if(i, post);
	main_pic(w, 0);
	if (pre != NULL)
		type_str(w, w->txthead, pre, 0x12FEA800);
	if (i == 2)
		type_str(w, dot, "Saving modif...", 0x12FEA800);
	else
		type_str(w, dot, "Loading game...", 0x12FEA800);
	img_update(w);
	if (post != NULL)
		free(post);
	if (pre != NULL)
		free(pre);
	if (i == 8 && s != NULL)
		free(s);
}

void			write_name_map(t_env *w, int nbmaps)
{
	char		*name;

	ft_light_itoa(nbmaps, w->light_nb);
	if ((name = ft_strjoin("MAP WILL BE CREATED AS MAP", w->light_nb)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strsplit"));
	main_pic(w, 0);
	w->txthead.x = 10;
	w->txthead.y = 10;
	type_str(w, w->txthead, name, 0x12FEA800);
	free(name);
}

void			process_hint_savemap(t_env *w, int i, int nbmaps, char *s)
{
	char		*pre;
	char		*post;
	t_dot		dot;

	write_name_map(w, nbmaps);
	w->txthead.x = 6;
	w->txthead.y = 550;
	dot.x = 800;
	dot.y = 550;
	if (i == 2)
		s = ft_strjoinnfree(s, " %", 1);
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (post != NULL)
		pre = ft_strjoinnfree("Writing ... ", post, 2);
	if (pre != NULL)
		type_str(w, w->txthead, pre, 0x12FEA800);
	type_str(w, dot, "Saving map...", 0x12FEA800);
	img_update(w);
	if (pre != NULL)
		free(pre);
	if (i == 2)
		free(s);
}
