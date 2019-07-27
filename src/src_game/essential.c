/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essential.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:58:24 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 19:22:52 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	sign(double a)
{
	return (((a) > 0) - ((a) < 0));
}

double	v_c_p(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

double	pointside(t_coor p, t_dot p0, double x1, double y1)
{
	return (sign(v_c_p(x1 - p0.x, y1 - p0.y, p.x - p0.x, p.y - p0.y)));
}

t_coor	intersect(t_intersect i)
{
	t_coor coor;
	double tmp1;
	double tmp2;
	double tmp3;
	double tmp4;

	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.x1 - i.x2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.x3 - i.x4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.x = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4,
		i.y3 - i.y4));
	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.y1 - i.y2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.y3 - i.y4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.y = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4,
		i.y3 - i.y4));
	coor.z = 0;
	return (coor);
}

t_dot	fill_t_dot(int x, int y)
{
	t_dot	dot;

	dot.x = x;
	dot.y = y;
	return (dot);
}
