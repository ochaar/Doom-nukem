/*BIG42HEADER*/

#include "doom.h"

void			init_world(t_env **w, t_map **m, int ac)
{
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct world"));
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct map"));
	set_basics(*w, *m, ac);
}

void			set_basics(t_env *w, t_map *m, int ac)
{
	w->m = m;
	m->world = w;
	set_w(w, ac);
	set_m(m);
	set_m_player(m);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;
	clock_t		go_go_go;
	clock_t		over;

	go_go_go = clock();
	w = NULL;
	m = NULL;
	cmd = NULL;
	init_world(&w, &m, ac);
	if (ac > 1)
		interpret_cmd(w, m, cmd, av);
	load_core(w, m);
	over = clock();
	w->loading_time = ((double)(over - go_go_go)) / CLOCKS_PER_SEC;
	printf("game loaded in %f seconds !\n", w->loading_time);
	launch(w, m);
	exit_game(w, m, 0);
	return (0);
}
