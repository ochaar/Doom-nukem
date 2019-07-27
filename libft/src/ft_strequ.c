/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 13:21:36 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/17 17:54:29 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;
	int diff;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while (s2[i] || s1[i])
		{
			diff = (s1[i] - s2[i]);
			if (diff != 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
