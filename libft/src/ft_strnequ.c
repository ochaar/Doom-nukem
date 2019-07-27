/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 19:53:23 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/16 21:32:09 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		while ((s2[i] || s1[i]) && i < n)
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
