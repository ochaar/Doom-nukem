/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 23:46:38 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/17 16:59:47 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_none(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (c);
	return (0);
}

char			*ft_strtrim(const char *s)
{
	char		*str;
	int			i;
	size_t		l;

	l = 0;
	if (s != NULL)
	{
		while (ft_none(*s) != 0)
			s++;
		while (s[l] != '\0')
		{
			i = 0;
			while (ft_none(s[i + l]) != 0)
				i++;
			if (i > 0 && s[i + l] == '\0')
				break ;
			else if (i > 0)
				l = l + i;
			l++;
		}
		str = ft_strnew(l);
		ft_memcpy(str, s, l);
		return (str);
	}
	return (NULL);
}
