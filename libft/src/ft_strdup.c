/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 13:37:21 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 06:54:19 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int			i;
	int			j;
	char		*s2;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	if ((s2 = (char *)ft_memalloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
