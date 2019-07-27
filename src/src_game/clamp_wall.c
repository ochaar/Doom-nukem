/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 02:25:03 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 15:29:49 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	calc_x1_to_x2(t_env *w, t_work *work)
{
	if (work->t1.z != 0)
	{
		work->xscale1 = w->m->player.field_of_vision_h / work->t1.z;
		work->yscale1 = (w->m->player.field_of_vision_v) / work->t1.z;
	}
	if (work->t2.z != 0)
	{
		work->xscale2 = w->m->player.field_of_vision_h / work->t2.z;
		work->yscale2 = (w->m->player.field_of_vision_v) / work->t2.z;
	}
	work->x1 = WIDTH / 2 - (int)(work->t1.x * work->xscale1);
	work->x2 = WIDTH / 2 - (int)(work->t2.x * work->xscale2);
}

void	clamp_wall_1(t_work *work)
{
	if (work->t1.z < work->nearz)
	{
		if (work->ip1.y > 0)
		{
			work->t1.x = work->ip1.x;
			work->t1.z = work->ip1.y;
		}
		else
		{
			work->t1.x = work->ip2.x;
			work->t1.z = work->ip2.y;
		}
	}
}

void	clamp_wall_2(t_work *work)
{
	if (work->t2.z < work->nearz)
	{
		if (work->ip1.y > 0)
		{
			work->t2.x = work->ip1.x;
			work->t2.z = work->ip1.y;
		}
		else
		{
			work->t2.x = work->ip2.x;
			work->t2.z = work->ip2.y;
		}
	}
}

void	init_clamp_wall(t_work *work)
{
	work->i1.x1 = work->t1.x;
	work->i1.y1 = work->t1.z;
	work->i1.x2 = work->t2.x;
	work->i1.y2 = work->t2.z;
	work->i1.x3 = -work->nearside;
	work->i1.y3 = work->nearz;
	work->i1.x4 = -work->farside;
	work->i1.y4 = work->farz;
	work->i2.x1 = work->t1.x;
	work->i2.y1 = work->t1.z;
	work->i2.x2 = work->t2.x;
	work->i2.y2 = work->t2.z;
	work->i2.x3 = work->nearside;
	work->i2.y3 = work->nearz;
	work->i2.x4 = work->farside;
	work->i2.y4 = work->farz;
	work->ip1 = intersect(work->i1);
	work->ip2 = intersect(work->i2);
}
