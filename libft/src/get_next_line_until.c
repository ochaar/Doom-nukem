/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_until.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 16:34:01 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 15:22:41 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static char			*ft_line(char *s)
{
	int				i;
	char			*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	str = ft_strnew(i);
	ft_strncpy(str, s, i);
	str[i] = '\0';
	return (str);
}

static char			*ft_stock(char *s)
{
	int				i;
	char			*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	str = ft_strdup(s + i + 1);
	ft_strdel(&s);
	return (str);
}

int					get_next_line_until(int const fd, char **line, int stop)
{
	t_gnlu			g;
	static char		*save;

	g.buff = ft_strnew(BUFF_SIZE + 1);
	save = (save == NULL) ? ft_strnew(1) : save;
	if (g.buff == NULL || BUFF_SIZE <= 0 || line == NULL)
		return (-1);
	g.ret = 42;
	while ((ft_strchr(save, '\n') == NULL) && g.ret > 0)
	{
		if ((g.ret = read(fd, g.buff, BUFF_SIZE)) == -1)
			return (-1);
		g.buff[g.ret] = '\0';
		g.temp = save;
		save = ft_strjoin(save, g.buff);
		ft_strdel(&g.temp);
	}
	ft_strdel(&g.buff);
	*line = ft_line(save);
	if (g.ret == 0 || stop == 1)
		ft_strdel(&save);
	if (g.ret == 0 && *line[0] == '\0')
		return (0);
	save = ft_stock(save);
	return (1);
}
