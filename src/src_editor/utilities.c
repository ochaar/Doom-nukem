/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:54:47 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:54:58 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		*strdup_safe(t_env *w, t_win *win, const char *s1)
{
	int			i;
	int			j;
	char		*s2;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	if (!(s2 = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		clear_n_exit(w, win);
	j = 0;
	while (s1[j])
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

void		ft_swap2(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		sort_int_tab(int *tab, int size)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			ft_swap2(&tab[i], &tab[i + 1]);
			sort_int_tab(tab, size);
		}
		i++;
	}
}

int			len_listlist(t_lstlst *lstlst)
{
	int			i;
	t_lstlst	*tmp2;

	i = 0;
	tmp2 = lstlst;
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	return (i);
}

int			total_number_of_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			len_dots;

	i = 0;
	len_dots = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		i = len_list(tmp);
		len_dots = len_dots + i;
		tmp2 = tmp2->next;
	}
	return (len_dots);
}
