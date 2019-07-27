/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 19:14:34 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 15:27:24 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	char	*t;

	mem = (void *)malloc(size);
	if (mem == NULL)
		return (NULL);
	t = (char *)mem;
	ft_bzero(t, size);
	return (mem);
}
