/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 12:52:11 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/16 16:43:43 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char *))
{
	int i;
	int l;

	i = 0;
	if (s != NULL && f != NULL)
	{
		l = ft_strlen(s);
		while (i < l)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
