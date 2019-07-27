/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:39:01 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 11:47:16 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	crux_x(t_vect vec, t_env *w, Uint32 color)
{
	int dx;

	dx = vec.x2 - vec.x1;
	if (dx > 0)
	{
		while (vec.x1 != vec.x2)
		{
			set_txtr_pix(w, vec.x1, vec.y1, color);
			vec.x1++;
		}
	}
	else
	{
		while (vec.x1 != vec.x2)
		{
			set_txtr_pix(w, vec.x1, vec.y1, color);
			vec.x1--;
		}
	}
}

void	crux_y(t_vect vec, t_env *w, Uint32 color)
{
	int dy;

	dy = vec.y2 - vec.y1;
	if (dy > 0)
	{
		while (vec.y1 != vec.y2)
		{
			set_txtr_pix(w, vec.x1, vec.y1, color);
			vec.y1++;
		}
	}
	else
	{
		while (vec.y1 != vec.y2)
		{
			set_txtr_pix(w, vec.x1, vec.y1, color);
			vec.y1--;
		}
	}
}

void	crux(t_vect norm, t_env *w, Uint32 color)
{
	if (norm.dy == 0)
		crux_x(norm, w, color);
	if (norm.dx == 0)
		crux_y(norm, w, color);
}

void	vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color)
{
	t_vect	norm;

	norm.x1 = p1.x;
	norm.y1 = p1.y;
	norm.x2 = p2.x;
	norm.y2 = p2.y;
	norm.dx = p2.x - p1.x;
	norm.dy = p2.y - p1.y;
	if (norm.dx == 0 || norm.dy == 0)
		crux(norm, w, color);
	vect_ab_oct(norm, w, color);
	if (norm.dx < 0 && norm.dy > 0 && -norm.dx >= norm.dy)
		octant_4(norm, w, color);
	if (norm.dx < 0 && norm.dy < 0 && norm.dx <= norm.dy)
		octant_5(norm, w, color);
	if (norm.dx < 0 && norm.dy < 0 && norm.dx > norm.dy)
		octant_6(norm, w, color);
	if (norm.dx > 0 && norm.dy < 0 && norm.dx < -norm.dy)
		octant_7(norm, w, color);
	if (norm.dx > 0 && norm.dy < 0 && norm.dx >= -norm.dy)
		octant_8(norm, w, color);
}
