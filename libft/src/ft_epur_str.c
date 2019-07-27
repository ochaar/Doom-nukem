/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/16 00:40:03 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 15:26:12 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			things(const char *src)
{
	int		hint;
	int		a;

	a = -1;
	hint = 0;
	while (*(src + ++a) != '\0')
	{
		if (*(src + a) == ' ' || *(src + a) == '\t')
			hint++;
	}
	return (hint);
}

char		*ft_epur_str(const char *src)
{
	int		count;
	int		a;
	char	*ret;

	a = 0;
	count = -1;
	ret = (char *)ft_memalloc(sizeof(char) * (ft_strlen(src)
		- things(src) + 1));
	if (ret == NULL)
		return (NULL);
	while (*(src + ++count + a) != '\0')
	{
		while (*(src + count + a) == ' ' || *(src + count + a) == '\t')
		{
			a++;
		}
		*(ret + count) = *(src + count + a);
	}
	return (ret);
}
