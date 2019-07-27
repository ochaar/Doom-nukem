/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 07:19:42 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 11:40:13 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_get_time(t_env *w, float time_lvl)
{
	char	*x;
	char	*toa;
	float	ent;
	int		dec;

	ent = time_lvl;
	dec = ((int)(10 * ent) % 10) * 100 + ((int)(100 * ent) % 10)
		* 10 + ((int)(1000 * ent) % 10);
	if ((toa = ft_itoa(ent)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((x = ft_strjoinnfree(toa, ".", 1)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strjoin"));
	if ((toa = ft_itoa(dec)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error itoa"));
	if ((x = ft_strjoinnfree(x, toa, 3)) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "error strjoin"));
	type_str(w, w->txtnxtto, x, 0x12FFFFFF);
	free(x);
}
