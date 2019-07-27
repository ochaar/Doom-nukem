/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:30:48 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 13:42:51 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isfloat(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1 || str[i] == '.')
		{
			if (str[i] == '.')
				count++;
		}
		else
			return (0);
		if (count > 1)
			return (0);
		i++;
	}
	return (1);
}
