/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 12:46:07 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/17 14:47:14 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	size_t i;
	size_t l;

	i = 0;
	if (s != NULL && f != NULL)
	{
		l = ft_strlen(s);
		while (i < l)
			f(&s[i++]);
	}
}
