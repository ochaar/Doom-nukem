/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:35:38 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/22 15:12:44 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			print_load(char *s, int i3, int len)
{
	char		*pre;
	char		*nb;
	char		*post;

	nb = ft_itoa((int)((double)i3 / (double)len * 100));
	post = ft_strjoin(nb, "\r");
	pre = ft_strjoin(s, post);
	ft_putstr(pre);
	free(nb);
	free(post);
	free(pre);
}

char			*other_if(int i, char *post)
{
	if (i == 2)
		return (ft_strjoin("initialisating ", post));
	if (i == 3)
		return (ft_strjoin("processing ", post));
	if (i == 4)
		return (ft_strjoin("parsing ", post));
	if (i == 5)
		return (ft_strjoin("running ", post));
	if (i == 6)
		return (ft_strjoin("loading ", post));
	if (i == 7)
		return (ft_strjoin("extracting ", post));
	return ("yes");
}

void			process_hint(int i, char *s)
{
	char		*pre;
	char		*post;

	ft_putstr("                                                        \r");
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("done", post);
	if (i == 1)
		pre = ft_strjoin("allocating memory for ", post);
	if (pre == NULL)
		pre = other_if(i, post);
	ft_putstr(pre);
	free(post);
	if (pre != NULL)
		free(pre);
}

void			process_hint_w(t_env *w, int i, char *s)
{
	char		*pre;
	char		*post;
	t_dot		dot;

	w->txthead.x = 6;
	w->txthead.y = 550;
	dot.x = 800;
	dot.y = 550;
	if (i == 2)
		s = ft_strjoinnfree(s, " %", 1);
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("Done", post);
	if (i == 1)
		pre = ft_strjoin("Allocating memory for ", post);
	if (i == 2)
		pre = ft_strjoin("Writing ... ", post);
	if (pre == NULL)
		pre = other_if(i, post);
	main_pic(w, 0);
	type_str(w, w->txthead, pre, 0x12FEA800);
	if (i == 2)
		type_str(w, dot, "Saving modif...", 0x12FEA800);
	else
		type_str(w, dot, "Loading game...", 0x12FEA800);
	img_update(w);
	free(post);
	if (pre != NULL)
		free(pre);
	if (i == 2)
		free(s);
}

void			process_hint_savemap(t_env *w, int i, int nbmaps, char *s)
{
	char		*name;
	char		*pre;
	char		*post;
	t_dot		dot;

	name = ft_strjoin("MAP WILL BE CREATED AS MAP", ft_itoa(nbmaps));
	main_pic(w, 0);
	w->txthead.x = 10;
	w->txthead.y = 10;
	type_str(w, w->txthead, name, 0x12FEA800);
	free(name);
	if (i == 2)
		s = ft_strjoinnfree(s, " %", 1);
	w->txthead.x = 6;
	w->txthead.y = 550;
	dot.x = 800;
	dot.y = 550;
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("Done", post);
	else
		pre = ft_strjoin("Writing ... ", post);
	if (pre == NULL)
		pre = other_if(i, post);
	type_str(w, w->txthead, pre, 0x12FEA800);
	type_str(w, dot, "Saving map...", 0x12FEA800);
	img_update(w);
	free(post);
	if (pre != NULL)
		free(pre);
	if (i == 2)
		free(s);
}
