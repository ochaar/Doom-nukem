/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:21:16 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 12:00:09 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		type_s(t_env *w)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = w->txt.x;
	y = w->txt.y;
	while (w->txt.text[i] != '\0')
	{
		ft_putmychar(w, i, &x, &y);
		i++;
	}
	w->txtnxtline.x = w->txt.x;
	w->txtnxtline.y = y + w->ascii[0].h + 5;
	w->txtnxtto.x = x;
	w->txtnxtto.y = y;
}

void		type_str(t_env *w, t_dot dot, char *s, Uint32 color)
{
	if (w->asciichk == ASCIINB)
	{
		w->txt.x = dot.x;
		w->txt.y = dot.y;
		w->txt.text = s;
		w->txt.color = color;
		type_s(w);
	}
}

void		print_story_helper(t_env *w, t_dot dot, t_dot dot2)
{
	if (ft_strcmp(w->currmap, "branch") == 0 && w->m->player.sector == 13)
	{
		type_str(w, dot, SCENAR_5, 0xFFFFFF);
		type_str(w, dot2, SCENAR_6, 0xFFFFFF);
	}
	if (ft_strcmp(w->currmap, "parkour") == 0 && w->m->player.sector == 4)
	{
		type_str(w, dot, SCENAR_7, 0xFFFFFF);
		type_str(w, dot2, SCENAR_8, 0xFFFFFF);
	}
	if (ft_strcmp(w->currmap, "three_steps") == 0 && w->m->player.sector == 0)
	{
		type_str(w, dot, SCENAR_9, 0xFFFFFF);
		type_str(w, dot2, SCENAR_10, 0xFFFFFF);
	}
	if (ft_strcmp(w->currmap, "three_steps") == 0 && w->m->player.sector == 17)
	{
		type_str(w, dot, SCENAR_11, 0xFFFFFF);
		type_str(w, dot2, SCENAR_12, 0xFFFFFF);
		dot2.y += 20;
		type_str(w, dot2, SCENAR_13, 0xFFFFFF);
	}
}

void		print_story(t_env *w)
{
	t_dot		dot;
	t_dot		dot2;

	dot.x = WIDTH / 3;
	dot.y = HEIGHT / 2 + 50;
	dot2.x = WIDTH / 3;
	dot2.y = HEIGHT / 2 + 70;
	if (ft_strcmp(w->currmap, "hsh") == 0 && w->m->player.sector == 4)
	{
		type_str(w, dot, SCENAR_1, 0xFFFFFF);
		type_str(w, dot2, SCENAR_2, 0xFFFFFF);
	}
	if (ft_strcmp(w->currmap, "branch") == 0 && w->m->player.sector == 7)
	{
		type_str(w, dot, SCENAR_3, 0xFFFFFF);
		type_str(w, dot2, SCENAR_4, 0xFFFFFF);
	}
	print_story_helper(w, dot, dot2);
}
