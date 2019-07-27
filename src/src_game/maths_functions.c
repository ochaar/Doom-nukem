/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:05:55 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/20 16:06:24 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	yaw(double y, double z, t_map *m)
{
	return (y + z * m->player.yaw);
}

double	pythagore(double a, double b)
{
	return (sqrt(a * a + b * b));
}

double	vabs(double a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}
