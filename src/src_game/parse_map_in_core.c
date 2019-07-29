/*BIG42HEADER*/

#include "doom.h"

void	reset_map(t_map *m)
{
	int i;

	i = 0;
	ft_free_tab(m);
	ft_free_sector(m);
	if (m->dot != NULL)
	{
		free(m->dot);
		m->dot = NULL;
	}
	ft_free_sprt(m);
	if (m->ennemy != NULL)
	{
		free(m->ennemy);
		m->ennemy = NULL;
	}
	if (m->linklvl != NULL)
	{
		free(m->linklvl);
		m->linklvl = NULL;
	}
	m->endsector = -1;
	m->change_lvl = 0;
	m->newgame = 0;
}

int		get_that_map_parsed(t_env *w, t_map *m)
{
	free(m->line);
	set_count(m);
	m->section_number = 0;
	process_hint_w(w, 6, "map");
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
	while (get_next_line_until(m->fd, &m->line, w->stopread) && w->stopread == 0)
	{
		if ((parse_line(w, m)) == -1)
		{
			write(2, "error on map collect\n", 22);
			free(m->line);
			return (-1);
		}
		free(m->line);
	}
	free(m->line);
	process_hint_w(w, 0, " ");
	if (m->dotsc != m->dots_count || m->s != m->sector_count
		|| m->spmc != m->sprite_map_count || m->ennemyc != m->ennemy_count)
		return (-1);
	return (0);
}

int			parse_map_in_core(t_env *w, t_map *m, char *name)
{
	char	*tmp;
	char	*pre;
	int		i;

	i = 0;
	w->stopread = 0;
	pre = ft_strdup("map\t\t\t;");
	tmp = ft_strjoin(pre, name);
	reset_map(m);
	reset_player(w, m);
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(m->fd, &m->line, w->stopread) && w->stopread == 0)
		{
			if (ft_strcmp(m->line, tmp) == 0)
			{
				if (get_that_map_parsed(w, m) != 0)
				{
					w->menu.i = 1;
					w->stopread = 1;
					w->m->newgame = 1;
					get_next_line_until(m->fd, &m->line, w->stopread);
					free(m->line);
					return (-1);
				}
			}
			else if (ft_strcmp(m->line, "ENDMAPSECTION") == 0)
			{	
				w->menu.i = 1;
				w->stopread = 1;
				w->m->newgame = 1;
				free(m->line);
				continue;
			}
			else
				free(m->line);
		}
		free(m->line);
		close(m->fd);
	}
	else
		set_error(w, m, 5, "core/core.dn3d");
	free(tmp);
	free(pre);
	return (0);
}

int			get_nb_maps_in_core(t_env *w)
{
	char	*line;
	int		nbmaps;
	int		fd;

	nbmaps = 0;
	w->stopread = 0;
	if ((fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(fd, &line, w->stopread) && w->stopread == 0)
		{
			if (ft_strncmp(line, "map\t\t\t", 6) == 0)
				nbmaps++;
			if (ft_strncmp(line, "ENDMAPSECTION", 13) == 0)
			{	
				free(line);
				w->stopread = 1;
				continue;
			}
			free(line);
		}
		free(line);
		close(fd);
	}
	else
		set_error(w, w->m, 5, "core/core.dn3d");
	return (nbmaps);
}

int			get_names_maps_in_core(t_env *w, char **names)
{
	char	**tmp;
	char	*pre;
	char	*line;
	int		maps;
	int		fd;

	maps = 0;
	w->stopread = 0;
	pre = ft_strdup("map\t\t\t");
	if ((fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(fd, &line, w->stopread) && w->stopread == 0)
		{
			tmp = ft_strsplit(line, ';');
			if (ft_strcmp(tmp[0], pre) == 0)
			{
				names[maps] = ft_strdup(tmp[1]);
				maps++;
			}
			ft_memreg(tmp);
			if (ft_strcmp(line, "ENDMAPSECTION") == 0)
			{	
				free(line);
				w->stopread = 1;
				continue;
			}
			free(line);
		}
		free(line);
		close(fd);
	}
	else
		set_error(w, w->m, 5, "core/core.dn3d");
	free(pre);
	return (0);
}
