/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octant.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:40:22 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 11:41:07 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	octant_4(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dy;
		if (e >= 0)
		{
			norm.y1++;
			e = e + dx;
		}
		norm.x1--;
	}
}

void	octant_5(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dy;
		if (e >= 0)
		{
			norm.y1--;
			e = e + dx;
		}
		norm.x1--;
	}
}

void	octant_6(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dx;
		if (e >= 0)
		{
			norm.x1--;
			e = e + dy;
		}
		norm.y1--;
	}
}

void	octant_7(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dx;
		if (e > 0)
		{
			norm.x1++;
			e = e + dy;
		}
		norm.y1--;
	}
}

void	octant_8(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dy;
		if (e < 0)
		{
			norm.y1--;
			e = e + dx;
		}
		norm.x1++;
	}
}
