/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 04:58:10 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 07:22:10 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_tab_exit(t_env *w, char **tab, int check)
{
	int		len;

	len = ft_tab_len(tab);
	if (len != check)
		set_error(w, w->m, 911, strdup_check(w, PAKOMSA));
	return (len);
}

int			check_tab(char **tab, int check)
{
	int		len;

	len = ft_tab_len(tab);
	if (len != check)
		return (-1);
	else
		return (0);
}

char		*strdup_check(t_env *w, char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	if ((s2 = (char *)ft_memalloc(sizeof(char) * (i + 1))) == NULL)
		set_error(w, w->m, 0, strdup_check(w, "strdup error"));
	j = 0;
	while (s1[j])
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
