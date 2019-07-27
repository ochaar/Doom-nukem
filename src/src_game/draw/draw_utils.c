/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 02:26:35 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 02:28:18 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	clean_render(t_env *w, Uint32 color)
{
	int x;

	x = 0;
	while (x < HEIGHT * WIDTH)
	{
		w->pix[x] = color;
		x++;
	}
}

void	sequential_draw_render(t_env *w)
{
	if (w->sequential_draw == 1 || w->sequential_frame == 1)
	{
		SDL_Delay(400);
		img_update(w);
	}
}

void	calc_z(t_work *work, int x)
{
	work->z = ((x - work->x1) * (work->t2.z - work->t1.z)
		/ (work->x2 - work->x1) + work->t1.z) * 2;
	work->z = vmin(work->z, 255);
}
