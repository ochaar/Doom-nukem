/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 15:30:34 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/14 16:24:47 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*t;

	i = 0;
	if (c == 0)
		return ((char *)&s[ft_strlen(s)]);
	t = (char *)s;
	while (t[i])
	{
		if (t[i] == (char)c)
			return (t + i);
		i++;
	}
	return (NULL);
}
