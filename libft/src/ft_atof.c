/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:03:00 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 18:27:02 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_virgule(const char *str, double value)
{
	double	cpt;
	double	virgule;

	cpt = 1;
	if (*str == '.')
	{
		str++;
		virgule = 0;
		while ((*str <= '9') && (*str >= '0'))
		{
			virgule = (virgule * 10) + (*str - '0');
			cpt = cpt * 10;
			str++;
		}
		value = value - (virgule / cpt);
	}
	return (value);
}

double		ft_atof(const char *str)
{
	int		is_negative;
	double	value;

	is_negative = 0;
	value = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' ||
		*str == '\v' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	while ((*str <= '9') && (*str >= '0'))
	{
		value = (value * 10) - (*str - '0');
		str++;
	}
	value = ft_virgule(str, value);
	if (!is_negative)
		value = -value;
	return (value);
}
