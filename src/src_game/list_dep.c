/*BIG42HEADER*/

#include "doom.h"

void		recap_sector_specific(t_env *w, t_map *m, int i, char *spec)
{
	if (ft_strcmp(spec, "general") == 0)
		recap_sector_general(*m, i);
	else if (ft_strcmp(spec, "dots") == 0)
		recap_sector_dots(*m, i);
	else if (ft_strcmp(spec, "network") == 0)
		recap_sector_network(*m, i);
	else
		set_error(w, m, 6, ft_strdup(spec));
}

void		recap_one(t_env *w, t_map *m, char **str, int i)
{
	if (i < m->sector_count)
	{
		if (str[3] == NULL)
			recap_sector(*m, i);
		else
			recap_sector_specific(w, m, i, str[3]);
	}
	else
		set_error(w, m, 7, ft_strdup(str[2]));
}

void		recap_all(t_env *w, t_map *m, char **str)
{
	int		i;

	i = 0;
	if (str[3] == NULL)
		recap_map_list_sectors(*m, str[2]);
	else
	{
		while (i < m->sector_count)
		{
			recap_sector_specific(w, m, i, str[3]);
			i++;
		}
	}
}

void		recap_map_list_sector(t_env *w, t_map *m, char **str)
{
	int		i;

	i = 0;
	if (str[2] != NULL)
	{
		if (ft_strcmp(str[2], "all") == 0)
			recap_all(w, m, str);
		else if (ft_isdigit(str[2][0]) == 1)
		{
			i = ft_atoi(str[2]);
			recap_one(w, m, str, i);
		}
		else
			set_error(w, m, 3, ft_strdup(str[2]));
	}
	ft_putchar('\n');
}

void		recap_map_list_sectors(t_map m, char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = str_to_upper(str);
	ft_putstr(s);
	free(s);
	ft_putendl(" :\n");
	while (i < m.sector_count)
	{
		recap_sector(m, i);
		i++;
	}
}
