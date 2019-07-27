/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 13:51:22 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/20 16:26:38 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	move_weap(t_env *w, t_map *m)
{
	m->player.bal = m->player.bal + w->sens;
	if (m->player.bal > 80)
		w->sens = -4 * m->player.movespeed;
	if (m->player.bal < -40)
		w->sens = 5 * m->player.movespeed;
}
