/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:16:18 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 11:03:09 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinnfree(char *s1, char *s2, int fr)
{
	int		l;
	char	*str;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (s1 != NULL && s2 != NULL)
	{
		l = ft_strlen(s1) + ft_strlen(s2);
		str = ft_strnew(l);
		if (!str || !s1 || !s2)
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
		if (fr == 1 || fr == 3)
			free(s1);
		if (fr == 2 || fr == 3)
			free(s2);
		return (str);
	}
	return (0);
}
