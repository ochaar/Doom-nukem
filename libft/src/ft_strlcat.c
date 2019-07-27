/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 14:48:12 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/22 20:32:57 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size <= lendst)
		return (lensrc + size);
	if (lensrc < size - lendst)
	{
		ft_memcpy(dst + lendst, src, lensrc);
		dst += lendst + lensrc;
	}
	else if (lensrc >= size - lendst)
	{
		ft_memcpy(dst + lendst, src, size - lendst - 1);
		dst = dst + size - 1;
	}
	*dst = '\0';
	return (lendst + lensrc);
}
