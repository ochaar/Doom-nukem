/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:01:05 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/20 16:08:00 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	vmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	vmax(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	vmid(double a, double min, double max)
{
	return (vmin(vmax(a, min), max));
}

double	isoverlap(double a0, double a1, double b0, double b1)
{
	if ((vmin(a0, a1) <= vmax(b0, b1) && vmin(b0, b1) <= vmax(a0, a1)))
		return (1);
	else
		return (0);
}

double	intersectbox(t_intersect i)
{
	if (isoverlap(i.x1, i.x2, i.x3, i.x4)
		&& isoverlap(i.y1, i.y2, i.y3, i.y4))
		return (1);
	else
		return (0);
}
