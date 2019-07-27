/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_get_next_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 16:34:01 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 07:15:11 by nvienot          ###   ########.fr       */
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

static void			ft_norme(char **buff, char **line, char **save, int ret)
{
	ft_strdel(buff);
	*line = ft_line(*save);
	if (ret == 0)
		ft_strdel(save);
}

int					precise_get_next_line(int const fd, char **line, int size)
{
	int				ret;
	char			*temp;
	static char		*save;
	char			*buff;

	buff = ft_strnew(size + 1);
	save = (save == NULL) ? ft_strnew(1) : save;
	if (buff == NULL || size <= 0 || line == NULL)
		return (-1);
	ret = 42;
	while ((ft_strchr(save, '\n') == NULL) && ret > 0)
	{
		if ((ret = read(fd, buff, size)) == -1)
			return (-1);
		buff[ret] = '\0';
		temp = save;
		save = ft_strjoin(save, buff);
		ft_strdel(&temp);
	}
	ft_norme(&buff, line, &save, ret);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	save = ft_stock(save);
	return (1);
}
