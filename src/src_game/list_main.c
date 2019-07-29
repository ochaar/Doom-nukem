/*BIG42HEADER*/

#include "doom.h"

void		recap_player_list_vars(t_map m, char *str)
{
	char	*s;

	s = str_to_upper(str);
	ft_putstr(s);
	free(s);
	ft_putendl(" :\n");
	ft_putstr("player_sector = ");
	ft_putnbrendl((int)m.player.sector);
	ft_putstr("player_coor : x = ");
	ft_putnbr((int)m.player.coor.x);
	ft_putstr(", y = ");
	ft_putnbrendl((int)m.player.coor.y);
	ft_putstr("player_direction = ");
	ft_putnbrendl((int)m.player.angle);
	ft_putchar('\n');
}

void		recap_map_list_general(t_map m, char *str)
{
	char	*s;

	s = str_to_upper(str);
	ft_putstr(s);
	free(s);
	ft_putendl(" :\n");
	ft_putstr("map_section_count = ");
	ft_putnbrendl(m.section_number);
	ft_putstr("map_dots_count = ");
	ft_putnbrendl(m.dots_count);
	ft_putstr("map_sector_count = ");
	ft_putnbrendl(m.sector_count);
	ft_putstr("map_name = ");
	ft_putendl(m.map_name);
	ft_putstr("map_path = ");
	ft_putendl(m.map_path);
	ft_putchar('\n');
}

void		recap_map_list_dots(t_map m, char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = str_to_upper(str);
	ft_putstr(s);
	free(s);
	ft_putendl(" :\n");
	while (i < m.dots_count)
	{
		ft_putstr("dot_");
		ft_putnbr(i);
		ft_putstr(" : x = ");
		ft_putnbr((int)m.dot[i].x);
		ft_putstr(", y = ");
		ft_putnbrendl(m.dot[i].y);
		i++;
	}
	ft_putchar('\n');
}

void		recap_parsing(t_env *w, t_map *m, char **str)
{
	if (ft_strcmp(str[1], "map_general") == 0)
		recap_map_list_general(*m, str[1]);
	else if (ft_strcmp(str[1], "map_dots") == 0)
		recap_map_list_dots(*m, str[1]);
	else if (ft_strncmp(str[1], "map_sector", 10) == 0)
	{
		if (ft_strcmp(str[1], "map_sectors") == 0)
			recap_map_list_sectors(*m, str[1]);
		else if (ft_strcmp(str[1], "map_sector") == 0)
			recap_map_list_sector(w, m, str);
	}
	else if (ft_strcmp(str[1], "player_vars") == 0)
		recap_player_list_vars(*m, str[1]);
	else
		ft_putstr("invalid section");
}
