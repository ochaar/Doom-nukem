/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 00:53:18 by cglavieu          #+#    #+#             */
/*   Updated: 2015/05/08 12:55:56 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*str;

	str = NULL;
	if ((str = (char *)malloc(sizeof(char *) * size + 1)))
	{
		while (size)
			str[size--] = '\0';
		str[0] = '\0';
	}
	return (str);
}
