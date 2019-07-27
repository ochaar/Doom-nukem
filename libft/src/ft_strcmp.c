/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:58:18 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/15 21:24:27 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int diff;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (s1[i] && s2[i])
	{
		diff = ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (diff != 0)
			return (diff);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
