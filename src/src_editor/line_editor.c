/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:28:48 by abechet           #+#    #+#             */
/*   Updated: 2019/07/13 17:40:47 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	line(t_env *w, t_win *win, t_dot tmp, t_dot tmp2)
{
	t_coor p1;
	t_coor p2;

	p1.x = tmp.x;
	p1.y = tmp.y;
	p2.x = tmp2.x;
	p2.y = tmp2.y;
	vect_ab(p1, p2, w, win->color);
}
