/*BIG42HEADER*/

#include "doom.h"

void		video_mode_cmd(t_env *w, t_map *m, char ***cmd, int i)
{
	if (cmd[i][1] != NULL)
	{
		if (ft_strcmp(cmd[i][1], "FULL_SCREEN") == 0)
			w->window_mode = FULL_SCREEN;
		else if (ft_strcmp(cmd[i][1], "RESIZABLE_SCREN") == 0)
			w->window_mode = RESIZABLE_SCREEN;
		else
			set_error(w, m, 3, ft_strdup(cmd[i][1]));
	}
}

void		map_cmd(t_env *w, t_map *m, char **cmd)
{
	char	**tmp;
	char	**tmp2;

	if (cmd[1] == NULL)
		set_error(w, m, 3, ft_strdup("no map specified"));
	free(m->map_path);
	m->map_path = ft_strdup(cmd[1]);
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
		set_error(w, m, 3, ft_strdup("incorrect format"));
	tmp2 = ft_strsplit(tmp[1], '.');
	free(m->map_name);
	m->map_name = ft_strdup(tmp2[0]);
	ft_memreg(tmp);
	ft_memreg(tmp2);
	m->launchwmap = 1;
}

void		ft_trucage(char *s)
{
	int i;

	i = 2;
	if (ft_strlen(s) > 2)
	{
		while (s[i] != '\0')
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

void		extract_bmp(t_env *w, t_map *m, char **cmd)
{
	t_texture	texture;
	int			i;
	int			index;
	char		*str;

	index = 1;
	while (cmd[index] != NULL)
	{
		i = 0;
		texture = load_img(w, m, cmd[index]);
		ft_putstr("\tnew:");
		ft_putnbr(texture.w);
		ft_putchar(',');
		ft_putnbr(texture.h);
		ft_putchar(':');
		while (i < texture.w * texture.h)
		{
			str = ft_uitoa_base(texture.pix[i], 16);
			ft_trucage(str);
			i++;
			if (i < texture.w * texture.h)
				ft_putchar(',');
			free(str);
		}
		ft_putchar('\n');
		free(texture.pix);
		index++;
	}
	exit_game(w, m, 1);
}

void		not_a_command(t_env *w, t_map *m, char ***cmd, char *s)
{
	ft_memreg3(cmd);
	set_error(w, m, 2, ft_strdup(s));
}

void		interpret_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int		ac;
	int		i;

	i = 0;
	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		while (cmd[i] != NULL)
		{
			if (ft_strcmp(cmd[i][0], "-video_mode") == 0)
				video_mode_cmd(w, m, cmd, i);
			else if (ft_strcmp(cmd[i][0], "-map") == 0)
				map_cmd(w, m, cmd[i]);
			else if (ft_strcmp(cmd[i][0], "-extract_bmp") == 0)
				extract_bmp(w, m, cmd[i]);
			else
				not_a_command(w, m, cmd, ft_strdup(cmd[i][0]));
			i++;
		}
	}
	else
		set_error(w, m, 1, ft_strdup(av[1]));
	ft_memreg3(cmd);
}
