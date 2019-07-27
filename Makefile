# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 15:00:20 by nvienot           #+#    #+#              #
#    Updated: 2019/07/25 17:41:58 by nvienot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash
CC = gcc

ifneq ($(wildcard ./core/core.dn3d),)
	ZIP				=	echo -e "\033[38;5;79m[core.dn3d] found, no extract needed !\033[0m"
else
	ZIP				=	echo -e "\033[38;5;79m[core.dn3d] not found, let's extract it !" && unzip ./core/core.dn3d.zip && mv ./core.dn3d ./core && echo -e "Extract done\033[0m"
endif


NAME                =   doom-nukem
CFLAG       		=   -Wall -Wextra -Werror -O2
MESSAGE     		=   "\033[38;5;79m[$(NAME)] compiled on normal rules ! Have fun\033[0m                          "

INCDIR              =   ./inc/
OBJDIR              =   ./obj/
LIBFTDIR            =   ./libft/
SRCDIR              =   ./src/

INCFIL              =   doom.h
OBJFIL              =   $(SRCFIL:.c=.o)
LIBFTFIL            =   libft.a
SRCFIL				=	src_game/main.c \
						src_game/draw/draw_high.c \
						src_game/draw/draw_launch.c \
						src_game/draw/draw_low.c \
						src_game/draw/draw_main.c \
						src_game/draw/draw_map.c \
						src_game/draw/draw_minimap.c \
						src_game/draw/draw_render.c \
						src_game/draw/draw_sprite.c \
						src_game/draw/draw_txtr_utils.c \
						src_game/draw/draw_utils.c \
						src_game/draw/draw_wall.c \
						src_game/draw/draw_ceil_floor_sky.c \
						src_game/menu/menu.c \
						src_game/menu/menu_level_n_loose.c \
						src_game/menu/menu_maps.c \
						src_game/menu/menu_screen.c \
						src_game/menu/menu_settings.c \
						src_game/menu/menu_utils.c \
						src_game/parser/core_load_core.c \
						src_game/parser/core_parse_allocations.c \
						src_game/parser/core_parse_settings.c \
						src_game/parser/core_parse_sprite.c \
						src_game/parser/core_parse_texture.c \
						src_game/parser/core_parse_weapon.c \
						src_game/parser/map_first_line.c \
						src_game/parser/map_nb_names.c \
						src_game/parser/map_parse_dots.c \
						src_game/parser/map_parse_ennemy.c \
						src_game/parser/map_parse_line.c \
						src_game/parser/map_parse_sector.c \
						src_game/parser/map_parse_sprites.c \
						src_game/parser/map_player_section.c \
						src_game/parser/parse_map_in_core.c \
						src_game/text/mytext.c \
						src_game/text/putmychar.c \
						src_game/add_map_to_core.c \
						src_game/check.c \
						src_game/cmd_exec.c \
						src_game/cmd_parse.c \
						src_game/doom_functions.c \
						src_game/clamp_wall.c \
						src_game/elevadoor.c \
						src_game/ennemy.c \
						src_game/error.c \
						src_game/essential.c \
						src_game/exit.c \
						src_game/fall_and_stair.c \
						src_game/fill_tab.c \
						src_game/ft_free.c \
						src_game/ft_free_next.c \
						src_game/game_functions.c \
						src_game/go_player.c \
						src_game/handed.c \
						src_game/hud.c \
						src_game/init.c \
						src_game/init_2.c \
						src_game/init_moving.c \
						src_game/key_events.c \
						src_game/keydown_events.c \
						src_game/keyup_events.c \
						src_game/line_vec.c \
						src_game/look_around.c \
						src_game/maths_functions.c \
						src_game/modif_file.c \
						src_game/mouse_events.c \
						src_game/moving_ennemy.c \
						src_game/moving_functions.c \
						src_game/moving_z_functions.c \
						src_game/multithreading.c \
						src_game/octant.c \
						src_game/octant_2.c \
						src_game/process_hint.c \
						src_game/put_to_screen.c \
						src_game/put_to_screen_utils.c \
						src_game/run_oc.c \
						src_game/set_basics.c \
						src_game/set_m.c \
						src_game/sprite.c \
						src_game/utils.c \
						src_game/visibility.c \
						src_game/weapon.c \
						src_game/set_fire.c \
						src_editor/correct_map.c \
						src_editor/delete_asset.c \
						src_editor/delete_mode.c \
						src_editor/dot_per_line.c \
						src_editor/first_line.c \
						src_editor/free_editor.c \
						src_editor/manage_sdl_window.c \
						src_editor/launch_editor.c \
						src_editor/init_editor.c \
						src_editor/grid.c \
						src_editor/init_editor.c \
						src_editor/launch_editor.c \
						src_editor/line_editor.c \
						src_editor/list.c \
						src_editor/loop.c \
						src_editor/loop2.c \
						src_editor/loop3.c \
						src_editor/manage_sdl_window.c \
						src_editor/map_save.c \
						src_editor/new_poly.c \
						src_editor/nopis.c \
						src_editor/params.c \
						src_editor/placing.c \
						src_editor/placing2.c \
						src_editor/point_triangulate.c \
						src_editor/polygone.c \
						src_editor/sdl_event.c \
						src_editor/sdl_keyboard_event.c \
						src_editor/sdl_mouse_event.c \
						src_editor/sort_points.c \
						src_editor/sort_triangles_points.c \
						src_editor/texture_mode.c \
						src_editor/texture_mode2.c \
						src_editor/triang_player_start.c \
						src_editor/triangle_neighbours.c \
						src_editor/triangulate.c \
						src_editor/triangulate2.c \
						src_editor/triangulate_all_assets.c \
						src_editor/undo.c \
						src_editor/utilities.c \
						src_editor/vertex.c \
						src_editor/write_dots.c \
						src_editor/write_in_file.c \
						src_editor/write_player.c \
						src_editor/write_sectors.c \
						src_editor/write_sprites.c \
						src_editor/write_weapons.c \
						src_editor/xy_on_line.c \
						src_editor/on_top.c \
						src_editor/correct_intersect.c

SRC                 =   $(addprefix $(SRCDIR),$(SRCFIL))
OBJ                 =   $(addprefix $(OBJDIR),$(OBJFIL))
LIBFT               =   $(addprefix $(LIBFTDIR),$(LIBFTFIL))
INC                 =   $(addprefix $(INCDIR),$(INCFIL))
INCLIBFT            =   $(LIBFTDIR)inc
LIBFT_FLAG          =   -L$(LIBFTDIR) -lft

SDL_PATH            =   ./SDL2-2.0.9/
LIBSDL_ROOT         =   ./libSDL2/
LIBSDL_PATH         =   ./libSDL2/lib/
LIBSDL              =   libSDL2.a
INCSDL              =   $(LIBSDL_ROOT)include/
LIBSDL_FLAG         =   -L$(LIBSDL_PATH) -lSDL2 -lSDL2_mixer
SDLBIN              =   $(addprefix $(LIBSDL_PATH),$(LIBSDL))
SDL_CURL            =   `curl https://www.libsdl.org/release/SDL2-2.0.9.zip -o sdl2.zip`

SDLMIX_PATH         =   ./SDL2_mixer-2.0.4/
LIBSDLMIX_ROOT      =   ./libSDL2/
LIBSDLMIX_PATH      =   ./libSDL2/lib/
LIBSDLMIX           =   libSDL2_mixer.a
INCSDLMIX           =   $(LIBSDLMIX_ROOT)include/
SDLMIXBIN           =   $(addprefix $(LIBSDLMIX_PATH),$(LIBSDLMIX))
CURL_MIX            =   `curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.zip -o sdl_mix.zip`

T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
PROGRESS = "[`expr $C '*' 100 / $T`%]"

all                 :   libft sdl sdlmix $(NAME)

$(NAME)             :   $(OBJ) $(LIBFT)
						@$(CC) $(CFLAG) -lm $(LIBFT_FLAG) $(LIBSDL_FLAG) -o $@ $^ -lpthread
						@echo -e $(MESSAGE)
						@$(ZIP)

$(OBJDIR)%.o        :   $(SRCDIR)%.c Makefile inc/defines.h inc/doom.h inc/structs.h
						@mkdir -p $(OBJDIR)
						@mkdir -p ./obj/src_game
						@mkdir -p ./obj/src_game/menu
						@mkdir -p ./obj/src_game/parser
						@mkdir -p ./obj/src_game/draw
						@mkdir -p ./obj/src_game/text
						@mkdir -p ./obj/src_editor
						@$(CC) $(CFLAG) -I $(INCDIR) -I $(INCLIBFT) -I $(INCSDL) -o $@ -c $<
						@echo -ne "[$(NAME)] progress : $(PROGRESS) | $@               \r"

libft               :   $(LIBFT)

$(LIBFT)            :   $(LIBFTDIR)
						@make -C $(LIBFTDIR)

sdl                 :   $(SDLBIN)

$(SDLBIN)           :
						$(SDL_CURL)
						unzip sdl2.zip
						rm sdl2.zip
						mkdir -p $(LIBSDL_ROOT)
						cd $(SDL_PATH) && ./configure --prefix=$(PWD)/$(LIBSDL_ROOT)
						make -C $(SDL_PATH)
						make install -C $(SDL_PATH)

sdlmix              :   $(SDLMIXBIN)

$(SDLMIXBIN)        : 
						$(CURL_MIX)
						unzip sdl_mix.zip
						rm sdl_mix.zip
						cd $(SDLMIX_PATH) && ./configure --prefix=$(PWD)/$(LIBSDLMIX_ROOT)
						make -C $(SDLMIX_PATH)
						make install -C $(SDLMIX_PATH)

clean               :
						@make -C $(LIBFTDIR) clean
						@rm -Rf  $(OBJDIR)

fclean              :
						@make -C $(LIBFTDIR) fclean
						@echo -ne "Cleaning [$(NAME)]... In progress...\r"
						@rm -Rf  $(OBJDIR)
						@rm -f $(NAME)
						@echo -e "Cleaning [$(NAME)] done !                           "

sdlclean            :
						rm -rf $(LIBSDL_ROOT)
						rm -rf $(SDL_PATH)
						rm -rf $(LIBSDLMIX_ROOT)
						rm -rf $(SDLMIX_PATH)

re                  :   fclean all
