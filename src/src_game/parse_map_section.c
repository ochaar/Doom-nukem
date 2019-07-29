/*BIG42HEADER*/

#include "doom.h"

int			parse_map_dots(t_map *m, char *y, char *x)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(x, ',');
	while (tmp[i] != NULL)
	{
		if (m->i < m->dots_count)
		{
			m->dot[m->i].x = ft_atof(tmp[i]);
			m->dot[m->i].y = ft_atof(y);
		}
		i++;
		m->i++;
		m->dotsc++;
	}
	if (m->i > m->dots_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}

int			parse_sector_network(t_map *m, char *net)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(net, ',');
	while (i < m->sector[m->s].wall_count && tmp[i] != '\0')
	{
		if (ft_strcmp(tmp[i], "x") != 0)
			m->sector[m->s].network[i] = ft_atoi(tmp[i]);
		else
			m->sector[m->s].network[i] = -1;
		i++;
	}
	if (i != m->sector[m->s].wall_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}

int			parse_sector_texturing(t_map *m, char *text)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(text, ',');
	while (i < 6)
	{
		m->sector[m->s].texturing[i] = ft_atoi(tmp[i]);
		i++;
	}
	ft_memreg(tmp);
	return (0);
}

int			parse_sector_dots(t_map *m, char **dots)
{
	int		i;
	int		mem[2];

	i = 0;
	mem[0] = 0;
	mem[1] = 0;
	while (i < m->sector[m->s].wall_count)
	{
		mem[0] = ft_atoi(dots[i]);
		if (mem[0] > m->dots_count - 1)
		{
			ft_putendl("Error on map file.");
			return (-1);
		}
		if (i == 0)
			mem[1] = mem[0];
		m->sector[m->s].dot[i].x = m->dot[mem[0]].x;
		m->sector[m->s].dot[i].y = m->dot[mem[0]].y;
		i++;
	}
	m->sector[m->s].dot[i].x = m->dot[mem[1]].x;
	m->sector[m->s].dot[i].y = m->dot[mem[1]].y;
	ft_memreg(dots);
	return (0);
}

int			parse_sectors(t_map *m, char *heights, char *dots, char *net, char *text)
{
	int		i;
	char	**tmp;

	i = 0;
	if (m->s < m->sector_count)
	{
		tmp = ft_strsplit(heights, ',');
		m->sector[m->s].floor = ft_atof(tmp[0]);
		m->sector[m->s].ceiling = ft_atof(tmp[1]);
		ft_memreg(tmp);
		tmp = ft_strsplit(dots, ',');
		while (tmp[i] != NULL)
			i++;
		m->sector[m->s].wall_count = i;
		if ((m->sector[m->s].dot = (t_dot *)malloc(sizeof(t_dot)
			* (m->sector[m->s].wall_count + 1))) == NULL)
			return (-1);
		if ((m->sector[m->s].network = (int *)malloc(sizeof(int)
			* m->sector[m->s].wall_count)) == NULL)
			return (-1);
		if (parse_sector_dots(m, tmp) == -1)
			return (-1);
		parse_sector_network(m, net);
		parse_sector_texturing(m, text);
	}
	else
		return (-1);
	m->s++;
	return (0);
}

int			parse_map_section(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tdots") == 0)
	{
		if (parse_map_dots(m, tab[1], tab[2]) == -1)
		{
			ft_putendl("error on parsing of the dot section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "\tsector") == 0)
	{
		if (parse_sectors(m, tab[1], tab[2], tab[3], tab[4]) == -1)
		{
			ft_putendl("error on parsing of the \"sector\" section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "Section") != 0)
		return (-1);
	return (0);
}
