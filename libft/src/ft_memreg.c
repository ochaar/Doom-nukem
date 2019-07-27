/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memreg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 02:45:28 by cglavieu          #+#    #+#             */
/*   Updated: 2015/12/19 16:27:42 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memreg3(char ***s)
{
	int i;
	int j;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			j = 0;
			while (s[i][j])
			{
				free(s[i][j]);
				s[i][j] = NULL;
				j++;
			}
			free(s[i]);
			s[i] = NULL;
			i++;
		}
		free(s);
	}
	s = NULL;
}

void	ft_memreg(char **s)
{
	int i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			free(s[i]);
			s[i] = NULL;
			i++;
		}
		free(s);
		s = NULL;
	}
}
