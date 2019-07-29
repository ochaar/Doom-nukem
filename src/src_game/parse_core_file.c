/*BIG42HEADER*/

#include "doom.h"

void			parse_weapon_line(t_map *m, char *line)
{
	char			**tmp;
	char			**tmp2;

	tmp2 = ft_strsplit(line, ':');
	m->weap[m->w].name = ft_strdup(tmp2[0]);
	tmp = ft_strsplit(tmp2[1], ',');
	if (tmp != NULL)
	{
		m->weap[m->w].range = ft_atoi(tmp[0]);
		if (tmp[1])
			m->weap[m->w].firerate = ft_atoi(tmp[1]);
		if (tmp[2])
			m->weap[m->w].accuracy = ft_atoi(tmp[2]);
		if (tmp[3])
			m->weap[m->w].dispertion = ft_atof(tmp[3]);
		if (tmp[4])
			m->weap[m->w].ammo_type = ft_atoi(tmp[4]);
		if (tmp[5])
			m->weap[m->w].magazine = ft_atoi(tmp[5]);
		if (tmp[6])
			m->weap[m->w].recoil = ft_atoi(tmp[6]);
	}
	if (tmp2[2])
		m->weap[m->w].reloadtime = ft_atof(tmp[2]);
	ft_memreg(tmp2);
	ft_memreg(tmp);
	m->w++;
}

void			parse_texture_line(t_env *w, t_map *m, char *line)
{
	char		**tmp;

	w->txthead.x = 800;
	w->txthead.y = 550;
	if ((tmp = ft_strsplit(line, ':')) == NULL)
		ft_putendl("ERREUR SPLIT");
	if (ft_strcmp(tmp[0], "ascii") == 0)
	{
		w->ascii[w->asciichk] = parse_texture(w, m, tmp);
		w->asciichk++;
	}
	if (ft_strcmp(tmp[0], "texturing") == 0)
	{
		w->texturing[w->texturingno] = parse_texture(w, m, tmp);
		w->texturingno++;
	}
	if (ft_strcmp(tmp[0], "main_pic[0]") == 0)
	{
		w->main_pic[0] = parse_texture(w, m, tmp);
		main_pic(w, 0);
		type_str(w, w->txthead, "loading game...", 0x12FEA800);
		img_update(w);
	}
	if (ft_strcmp(tmp[0], "main_pic[1]") == 0)
		w->main_pic[1] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "main_pic[2]") == 0)
		w->main_pic[2] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud") == 0)
		m->hud = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud2") == 0)
		m->hud2 = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "fire") == 0)
		m->fire = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "blackbox") == 0)
		m->whitebox = parse_texture(w, m, tmp);
	ft_memreg(tmp);
}

void			parse_sprite_line(t_env *w, t_map *m, char *line)
{
	char 		**tab;

	tab = ft_strsplit(line, ':');
	if (ft_strcmp(tab[0], "weapon_sprite") == 0)
	{
		process_hint_w(m->world, 4, "weapon sprite");
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
			set_error(w, m, 8, ft_strdup("weapon sprite"));
	}
	if (ft_strcmp(tab[0], "weapon_sprite") != 0)
	{
		if (parse_sprite_section(m, tab[0], tab[1], tab[2]) == -1)
			set_error(w, m, 8, ft_strdup("sprites"));
	}
	ft_memreg(tab);
}

void			parse_allocating_line(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	if (ft_strcmp(tmp[0], "weapon") == 0)
		m->weapon_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "ascii") == 0)
		w->asciino = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "sprite") == 0)
		m->sprite_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "texturing") == 0)
		m->texture_count = ft_atoi(tmp[1]);
	if (w->asciino > 0 && m->weapon_count > 0 && m->sprite_count > 0 && m->texture_count > 0)
	{
		if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon)
			* m->weapon_count)) == NULL)
				set_error(w, m, 0, ft_strdup("weapon"));
		if ((w->ascii = (t_texture *)malloc(sizeof(t_texture)
			* w->asciino)) == NULL)
				set_error(w, m, 0, ft_strdup("ascii"));
		if ((m->sprite = (t_sprite *)malloc(sizeof(t_sprite)
			* m->sprite_count)) == NULL)
				set_error(w, m, 0, ft_strdup("sprite"));
		if ((w->texturing = (t_texture *)malloc(sizeof(t_texture)
			* m->texture_count)) == NULL)
				set_error(w, m, 0, ft_strdup("texturing"));
		if (load_sounds(w, m) == -1)
		 	set_error(w, m, 8, ft_strdup("load_sounds"));
	}
	ft_memreg(tmp);
}

void			set_screen_res(t_env *w, char *aspect)
{
	w->window_res = ft_atoi(aspect);
	if (w->window_res == 0) //			16/9
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
	else if (w->window_res == 1)
	{
		w->res.width = 1920;
		w->res.height = 1080;
	}
	else if (w->window_res == 2)
	{
		w->res.width = 800;
		w->res.height = 600;
	}
	else
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
	w->game_res.width = w->res.width;
	w->game_res.height = w->res.height;
}

void			parse_settings_line(t_env *w, t_map *m, char *line)
{
	char **tmp;
	int check;

	check = 0;
	tmp = ft_strsplit(line, ':');
	while (tmp[check])
		check++;
	if (check != 5)
		set_error(w, m, 911, ft_strdup("error on core settings"));
	if (w->window_mode == -1)
		w->window_mode = ft_atoi(tmp[0]);
	set_screen_res(w, tmp[1]);
	m->player.field_of_vision_h = ft_atof(tmp[2]) * WIDTH / BASEWIDTH;
	m->player.field_of_vision_v = ft_atof(tmp[3]) * HEIGHT / BASEHEIGHT;
	w->mem_field_of_vision_h = m->player.field_of_vision_h;
	w->mem_field_of_vision_v = m->player.field_of_vision_v;
	m->player.mousesp = ft_atof(tmp[4]);
	ft_memreg(tmp);
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
}

void			load_core(t_env *w, t_map *m)
{
	int			buffer;
	char		*path;
	char		**tmp;
	double		loading;

	buffer = 128;
	w->dtime.start = SDL_GetTicks();
	path = ft_strdup("core/core.dn3d");
	if ((m->fd = open(path, O_RDONLY)) != -1)
	{
		while(precise_get_next_line(m->fd, &m->line, buffer))
		{
			if ((tmp = ft_strsplit(m->line, ';')) == NULL)
				ft_putendl("ERREUR SPLIT");
			if (ft_strncmp(m->line, "buffer", 6) == 0)
			{
				buffer = ft_atoi(tmp[1]);
				ft_memreg(tmp);
				free(m->line);
				continue;
			}
			else if (ft_strncmp(m->line, "settings", 8) == 0)
				parse_settings_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "alloc", 5) == 0)
				parse_allocating_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "weapon", 6) == 0)
				parse_weapon_line(m, tmp[1]);
			else if (ft_strncmp(m->line, "texture", 7) == 0)
				parse_texture_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "sprite", 6) == 0)
				parse_sprite_line(w, m, tmp[1]);
			if (ft_strncmp(m->line, "texture\t\t;ascii", 15) != 0
				&& ft_strncmp(m->line, "texture\t\t;main_pic", 18) != 0)
				buffer = 128;
			ft_memreg(tmp);
			free(m->line);
			w->corenbl++;
		}
		close(m->fd);
		free(m->line);
	}
	else
		set_error(w, m, 5, path);
	if (w->corenbl == 0)
		set_error(w, m, 911, ft_strdup(PAKOMSA));
	free(path);
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	w->nbmaps = get_nb_maps_in_core(w);
}
