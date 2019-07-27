/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:26:17 by agay              #+#    #+#             */
/*   Updated: 2019/07/25 18:55:02 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include "defines.h"
# include "structs.h"
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

void			parse_settings_line(t_env *w, t_map *m, char *line);
void			parse_allocating_line(t_env *w, t_map *m, char *line);
void			parse_weapon_line(t_map *m, char *line, t_babytrot *b);
void			parse_texture_line(t_env *w, t_map *m, char *l, t_babytrot *b);
void			parse_sprite_line(t_env *w, t_map *m, char *l, t_babytrot *b);
int				parse_map_in_core(t_env *w, t_map *m, char *name);
int				parse_map_line(t_env *w, t_map *m);
int				parse_first_line(t_map *m);
int				parse_map_dots(t_map *m, char **tab);
int				parse_sectors(t_map *m, char **tab, int check);
int				check_tab(char **tab, int check);
int				check_tab_exit(t_env *w, char **tab, int check);
int				parse_player_section(t_map *m, char **tab);
int				parse_ennemy_map(t_map *m, char **tab);
int				parse_sprite_map(t_map *m, char **tab);
char			***parse_cmd(int ac, char **av);
void			interpret_cmd(t_env *w, t_map *m, char ***cmd, char **av);
void			process_percent(t_env *w, int i, int type);
t_texture		pre_init_texture(int w, int h);
void			l_f_priority_cmd(t_env *w, t_map *m, char ***cmd);
void			map_cmd(t_env *w, t_map *m, char **cmd);
void			not_a_command(t_env *w, t_map *m, char ***cmd, char *s);
void			exit_cmd(t_env *w, t_map *m, char ***cmd);
void			video_mode_cmd(t_env *w, t_map *m, char ***cmd, int i);
void			seq_cmd(t_env *w, char ***cmd, int i);
void			set_error(t_env *w, t_map *m, int errorno, char *s);
void			set_basics(t_env *w, t_map *m, int ac);
void			set_count(t_map *m);
void			set_screen_res(t_env *w, char *aspect);
void			replace_line(char *path, char *balise, char *content, t_env *w);
void			add_map_to_core(char *path, char *path2, t_env *w, t_map *m);
void			change_settings(t_env *w, t_map *m);
void			init_map_structs(t_map *m);
int				quick_look(t_env *w, t_map *m);
void			set_advanced_run(char **av, t_env *w, t_map *m);
void			exit_game(t_env *w, t_map *m, int i);
int				init_sdl(t_env *w);
void			img_update(t_env *w);
void			clean_render(t_env *w, Uint32 color);
void			run(t_env *w, t_map *m);
Uint32			color(Uint32 color1);
void			vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color);
void			set_txtr_pix(t_env *w, int x, int y, Uint32 color);
double			vect_cross_prod(double x0, double y0, double x1, double y1);
void			vect_ab_oct(t_vect norm, t_env *w, Uint32 color);
void			octant_4(t_vect norm, t_env *w, Uint32 color);
void			octant_5(t_vect norm, t_env *w, Uint32 color);
void			octant_6(t_vect norm, t_env *w, Uint32 color);
void			octant_7(t_vect norm, t_env *w, Uint32 color);
void			octant_8(t_vect norm, t_env *w, Uint32 color);
double			sign(double a);
double			vabs(double a);
double			vmin(double a, double b);
double			vmax(double a, double b);
double			vmid(double a, double min, double max);
double			v_c_p(double x0, double y0, double x1, double y1);
double			intersectbox(t_intersect i);
t_coor			intersect(t_intersect i);
double			isoverlap(double a0, double a1, double b0, double b1);
double			pointside(t_coor p, t_dot p0, double x1, double y1);
double			yaw(double y, double z, t_map *m);
void			init_verification(t_work *draw);
void			moving_head(t_work *w, t_reader read, t_map *m);
int				check_invisible(t_work *d, t_reader read, t_map *m);
int				calcul_render_mthrd(t_env *w, t_work work, int *ybot,
	int *ytop);
void			calcul_render_no_mthrd(t_env *w, t_work *work);
void			key_events(t_env *w, t_map *m);
void			keydown_events(t_env *w, t_map *m);
void			keyup_events(t_env *w, t_map *m);
void			motion_events(t_env *w, t_map *m);
void			move_player(double dx, double dy, t_map *m);
void			get_height(t_map *m);
void			is_falling(t_map *m);
void			is_fall(t_map *m, int x);
void			slow_down(t_env *w, t_map *m);
void			is_moving(t_map *m);
void			move_all_ennemy(t_map *m);
void			walk_up_stairs(t_map *m, t_intersect i, int x, int s);
void			main_menu(t_env *w, t_map *m);
void			initsprite(t_sprite **sprite, int count);
void			hand(t_env *w, t_map *m);
void			buttondown_event(t_env *w, t_map *m);
void			buttonup_event(t_env *w, t_map *m);
void			main_pic(t_env *w, int nb);
int				load_sounds(t_env *w, t_map *m);
void			process_hint_w(t_env *w, int i, char *s);
void			set_config(t_env *w, t_map *m);
void			set_w(t_env *w, int ac);
void			set_m(t_map *m);
void			set_m_player(t_map *m);
void			load_core(t_env *w, t_map *m);
Uint32			*faster_please(t_map *m, Uint32 *dst, char *src, int len);
void			type_str(t_env *w, t_dot dot, char *s, Uint32 color);
void			ft_putmychar(t_env *w, int i, int *xmain, int *ymain);
void			go_forward(t_map *m);
void			go_back(t_map *m);
void			go_left(t_map *m);
void			go_right(t_map *m);
void			look_left(t_map *m);
void			look_right(t_map *m);
void			jump(t_env *w, t_map *m);
void			sprint(t_map *m);
void			ft_hud(t_env *w, t_map *m);
void			move_floor_ceiling(t_env *w, t_map *m);
void			game_img(t_env *w, t_map *m);
void			ramassage(t_map *m);
void			switch_weapon(t_map *m, int i);
void			look_around(t_env *w, t_map *m);
void			shoot(t_env *w, t_map *m);
void			reload_weapon(t_env *w, t_map *m);
void			move_weap(t_env *w, t_map *m);
void			elevator(t_map *m);
void			launch(t_env *w, t_map *m);
void			sequential_frame(t_env *w, t_map *m);
void			safe_char_to_screen(t_env *w, t_texture texture, int x, int y);
int				img_to_screen(t_env *w, t_texture texture, t_img img);
int				sprt_to_screen(t_env *w, t_sprite sprite, t_img img);
void			img_sequential_frame(t_env *w, int test);
int				test_limits_to_screen(t_img *img, t_scalling *s, t_env *w);
int				init_and_check_to_screen(t_scalling *s, t_env *w, t_img *img);
void			get_scalling(t_img *img, t_scalling *s, int text_w, int text_h);
t_img			fill_t_img(int x, int y, int w, int h);
void			get_that_time(t_env *w);
void			draw_sprite(t_env *w, t_map *m, int x, int ratio);
void			count_sprite(t_env *w, t_map *m);
void			test_sprite(t_map *m, double xx, double yy);
void			clear_sprite(t_map *m);
void			print_story(t_env *w);
int				rotate(t_cal_sprt data, int o);
void			draw_ennemy(t_env *w, t_map *m, int x, double ratio);
int				get_tmpix_scaled(t_sprite sprite, t_img img);
void			skybox(int x, t_env *w, t_work *work, t_texture text);
double			pythagore(double a, double b);
void			ennemy_animation(t_env *w, t_map *m, double **tab, int x);
double			**fill_tab_ennemy(t_map *m);
double			**fill_tab_sprite(t_map *m);
double			**sort_double_tab(double **tab, int size);
void			draw_high_line_t(int x, t_env *w, t_work *work,
	t_texture *text);
void			draw_ceiling_line_t(int x, t_env *w, t_work *work,
	t_texture *text);
void			draw_low_line_t(int x, t_env *w, t_work *work,
	t_texture *text);
void			draw_wall_line_t(int x, t_env *w, t_work *work,
	t_texture *text);
void			draw_textured_line(t_draw *d, t_env *w, t_work *work,
	t_texture *text);
void			check_start_end_tex(t_draw *d, t_work *work, t_texture *text);
void			ft_free_weap(t_map *m);
void			ft_free_sprite(t_map *m);
void			ft_free_sprt(t_map *m);
void			ft_free_sector(t_map *m);
void			ft_free_w(t_env *w);
void			reset_map(t_map *m);
void			reset_player(t_env *w, t_map *m);
void			fit_to_editor(t_env *w, t_win *win);
void			fit_to_game(t_env *w);
int				level_editor_start(t_env *w);
void			draw_grid(t_env *w);
void			clear_n_exit(t_env *w, t_win *win);
void			loop_play(t_env *w, t_win *win);
void			sdl_event(t_env *w, t_win *win);
void			sdl_event_mouse_right_click(t_env *w, t_win *win);
void			sdl_event_mouse_left_click(t_win *win, int x, int y,
	t_lst *tmp);
void			sdl_event_mouse_wheel(t_env *w, t_win *win, t_lstlst *tmp2);
void			sdl_event_key(t_env *w, t_win *win);
int				ft_round(int n);
t_lst			*lstnew(t_env *w, t_win *win, t_dot dot, int sector);
t_lstlst		*lstlstnew(t_env *w, t_win *win);
t_lstast		*lstastnew(t_env *w, t_win *win, int sector);
int				check_list(t_env *w, t_win *win, t_lst *lst, t_dot dot);
void			line(t_env *w, t_win *win, t_dot tmp, t_dot tmp2);
void			undo(t_win *win);
void			delete_sector(t_win *win);
int				point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m);
int				len_list(t_lst *lst);
t_lstlst		*recursive_triangulate(t_env *w, t_win *win, t_lstlst *tmp2,
	t_lst *polygone);
t_lstlst		*stock_triangles(t_win *win, t_lstlst *tmp3, t_lst *poly);
t_lstlst		*two_poly(t_win *win, t_lst *polygone, t_count cpt,
	t_lstlst *tmp3);
t_lst			*new_poly(t_win *win, t_lst *polygone, int start, int end);
int				*indice(t_env *w, t_win *win, t_count cpt);
int				near_vertex(int n, int i, int di);
int				left_vertex(t_lst *polygone, int len);
int				vertex_max_dist(t_lst *polygone, t_point p, int *tab);
t_lst			*polylstnew(t_win *win, t_dot d);
void			placing(t_win *win);
void			pick_asset(t_env *w, t_win *win);
void			mode(t_env *w, t_win *win);
int				len_listlist(t_lstlst *lstlst);
void			asset_overing(t_env *w, t_win *win);
void			texture_overing(t_win *win);
void			delete_asset(t_win *win);
void			overing(t_win *win);
void			on_click(t_env *w, t_win *win);
void			draw_points(t_env *w, int i, int j);
void			draw_segments(t_env *w, t_win *win);
void			draw_triangulate(t_env *w, t_win *win);
void			draw_asset_points(t_env *w, int i, int j, int color);
void			last_is_first(t_lst *lst);
void			och(t_env *w, t_win *win, t_lstlst *tmp2, int closed);
void			och3(t_win *win, t_lst *tmp, t_lstlst *tmp2, t_lstast *tmp3);
void			och5(t_win *win);
void			init_dst(t_win *win);
void			map_save(t_win *win, t_env *w);
void			check4(t_win *win);
char			*strdup_safe(t_env *w, t_win *win, const char *s1);
int				triangles_neighbours(t_env *w, t_win *win, t_lstlst *tmp2);
void			sort_triangles_points(t_env *w, t_win *win);
void			triangulate_all_assets(t_win *win);
int				triangulate_a_triangle(t_win *win, t_dot m);
int				correct_map(t_win *win);
void			mouse_wheel_helper(t_win *win);
void			fill_buffer(t_env *w, t_win *win);
int				sector_minimum_needed_point(t_win *win);
int				triangulate_player_start(t_win *win, int x, int y);
int				sector_intersect_with_itself(t_dot p1, t_dot p2, t_dot p3,
	t_dot p4);
int				check_player_start(t_win *win);
int				correct_intersections_in_a_sector(t_win *win);
void			write_ennemy(t_win *win, int fp, t_lstast *tmp, int i);
void			write_sprites(t_win *win, int fp);
void			write_ennemies(t_win *win, int fp);
void			write_shotgun_ammo(t_win *win, int fp, t_lstast *tmp, int i);
void			write_m4(t_win *win, int fp, t_lstast *tmp, int i);
void			write_m4_ammo(t_win *win, int fp, t_lstast *tmp, int i);
void			write_m9(t_win *win, int fp, t_lstast *tmp, int i);
void			write_shotgun(t_win *win, int fp, t_lstast *tmp, int i);
void			write_undertale(t_win *win, int fp, t_lstast *tmp, int i);
void			write_player(t_win *win, int fp);
void			write_sectors(t_env *w, t_win *win, int fp);
void			write_dots(t_env *w, t_win *win, int fp, int boole);
void			first_line2(t_env *w, t_win *win, int fp);
void			write_health(t_win *win, int fp, t_lstast *tmp, int i);
void			write_in_file(t_env *w, t_win *win);
int				y_min_point(t_win *win);
int				next_y(t_win *win, int y);
int				*create_y_dot_tab(t_env *w, t_win *win, int y, int i);
int				*dot_tab_sector(t_env *w, t_win *win, int sector);
int				*tab_sector3(t_env *w, t_win *win, int sector);
int				number_of_dot_per_line_with_same(t_win *win, int y);
int				total_exclusive_points(t_env *w, t_win *win);
int				number_of_dot_per_line(t_env *w, t_win *win, int y);
int				number_of_ennemy(t_win *win);
int				number_of_sprite(t_win *win);
int				number_of_y(t_win *win, t_lstlst *tmp2, t_lst *tmp);
int				x_min_on_line(t_win *win, int y);
int				next_x_on_line(t_win *win, int y, int x);
void			sort_points(t_env *w, t_win *win);
int				correct_three_points(t_win *win);
int				sector_inside_sector(t_win *win);
int				point_on_top(t_win *win);
int				sectors_on_top(t_lstlst *tmp2);
void			free_list(t_lst *lst);
void			free_listlist(t_win *win);
void			free_assets(t_win *win);
void			free_dot_tab(int *dot_tab);
void			sectors_in_tab(t_win *win);
void			sectors_in_tab2(t_win *win);
t_lstlst		*stock_last_triangle(t_win *win, t_lstlst *triangle,
	t_lstlst *tmp3, t_point p);
void			clear_window(t_win *win);
void			recursive_check(t_env *w, t_win *win);
void			sort_int_tab(int *tab, int size);
void			free_triangles(t_win *win);
int				int_len(int nb);
t_dot			get_point_in_list(t_lst *polygone, int index);
void			texture_mode(t_env *w, t_win *win);
void			change_texture_index(t_env *w, t_win *win);
void			set_params(t_env *w, t_win *win);
void			increase_value(t_win *win);
void			decrease_value(t_win *win);
int				init2(t_env *w, t_win *win);
double			pointside2(t_dot m, t_dot p0, double x1, double y1);
void			delete_sector2(t_win *win, t_lstlst *current,
	t_lstlst *previous);
int				get_nb_maps_in_core(t_env *w);
int				get_names_maps_in_core(t_env *w, t_map *m, char **names);
void			init_sprite_tab(t_map *m);
void			ft_free_tab(t_map *m);
void			process_hint_savemap(t_env *w, int i, int nbmaps, char *s);
void			draw(t_env *w, t_map *m);
int				render_wall(t_reader *read, t_work *work, t_env *w, int point);
void			draw_map(t_env *w, t_map *m);
void			draw_mini_map(t_env *w, t_map *m);
void			draw_ceiling_n_floor(t_work *work, t_env *w, int x);
void			draw_networks(t_work *work, t_env *w, int x);
void			draw_walls(t_work *work, t_env *w, int x);
void			sequential_draw_render(t_env *w);
void			init_clamp_wall(t_work *work);
void			clamp_wall_1(t_work *work);
void			clamp_wall_2(t_work *work);
void			calc_x1_to_x2(t_env *w, t_work *work);
int				dark_side(int color, t_work *work);
void			calc_z(t_work *work, int x);
int				fill_arg(int *nb, char *number);
void			menu_maps(t_env *w);
t_dot			fill_t_dot(int x, int y);
void			menu_settings(t_env *w);
void			affichage_set_str(t_env *w);
int				settings_changed(t_env *w);
void			change_value_settings(t_env *w, int direction);
int				menu_loose(t_env *w, t_map *m);
int				menu_change_lvl(t_env *w, t_map *m);
int				map_is_in_core(t_env *w, char *map);
void			menu_screen(t_env *w);
void			set_fire(t_env *w, t_map *m);
void			player_hole(t_map *m, int s);
void			init_x1_x2_mp(t_map *m, t_intersect *i, double dx, double dy);
void			init_x1nx2(t_map *m, t_intersect *i, int x);
void			init_x3nx4(t_map *m, t_intersect *i, int x, int s);
void			set_txtr_pix(t_env *w, int x, int y, Uint32 color);
void			set_txtr_dot(t_env *w, int x, int y, Uint32 color);
char			*strdup_check(t_env *w, char *str);
void			ft_get_time(t_env *w, float time_lvl);

#endif
