/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:29:41 by ochaar            #+#    #+#             */
/*   Updated: 2019/04/18 14:12:13 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_base(char c, int base)
{
	int		i;
	char	*def;

	i = 0;
	def = "0123456789ABCDEF";
	while (i < base)
	{
		if (def[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoui_base(const char *str, int base)
{
	unsigned int	ret;

	ret = 0;
	while (*str && *str != ' ')
	{
		if (find_base(ft_toupper(*str), base) != -1)
			ret = (ret * base) + find_base(ft_toupper(*str), base);
		str++;
	}
	return (ret);
}
