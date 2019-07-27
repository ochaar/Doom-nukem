/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:30 by abechet           #+#    #+#             */
/*   Updated: 2019/07/25 18:59:00 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define NAME 				"Doom-Nukem-3D"
# define BASEWIDTH 			1024
# define BASEHEIGHT 		576
# define WIN_X 				720
# define WIN_Y 				720
# define NB_THREADS 		8
# define FOV 				60
# define CUBE_SIZE 			64
# define MAP_MAX_LENGHT 	412
# define MAP_MAX_HEIGHT 	222
# define COLOR_WALL_NORTH 	16753920
# define COLOR_WALL_WEST 	16747520
# define COLOR_WALL_SOUTH 	16744220
# define COLOR_WALL_EAST 	16747320
# define COLOR_FLOOR 		9342606
# define COLOR_ROOF 		8900331
# define ERR_1 				"Usage : ./editor [map]"
# define ERR_2 				"Creation map error"
# define ERR_3 				"Map is only walls"
# define ERR_4 				"Initialization error"
# define ERR_5 				"Music load error"
# define ERR_6 				"Surface creation error"
# define ERR_7 				"SetRelativeMouseMode error"
# define ERR_8 				"SDL init error"
# define ERR_9 				"TTF init error"
# define ERR_10 			"Mix_OpenAudio error"
# define ERR_11 			"Window creation error"
# define ERR_12				"Renderer creation error"
# define ERR_13 			"TTF_OpenFont police load error"
# define ERR_14 			"SDL_Load error"
# define ERR_15 			"Mix_Load error"
# define ERR_16 			"Open error on map creation"
# define ERR_17 			"Render_copy error"
# define RESIZABLE_SCREEN	1
# define FULL_SCREEN		0
# define WIDTH 				w->res.width
# define HEIGHT 			w->res.height
# define WBW 				w->res.width / 1024
# define HBH 				w->res.height / 576
# define KEY 				w->event.key.keysym.sym
# define BUTTON				w->event.button.button
# define WINDOW				w->event.window.event
# define MRS				32
# define PL_X				m->player.coor.x
# define PL_MSX				m->player.move_speed.x
# define PL_Y				m->player.coor.y
# define PL_MSY				m->player.move_speed.y
# define PL_A				m->player.angle
# define PL_AC				m->player.anglecos
# define PL_AS				m->player.anglesin
# define PH					m->player.handed
# define M_S_C				m->sector_count
# define STAND				16.9
# define CROUCH				9.3
# define CRAWL				2
# define HEADMARGIN			1.1
# define KNEEH				7.9
# define BASE_GRAVITY		0.05
# define NB_THREAD			4
# define TEXT_WALL_HEIGHT	10
# define TEXT_WALL_WIDTH	10
# define PI					3.14159
# define ASCIINB			67
# define WIN_X				720
# define WIN_Y				720
# define GAME				0
# define EDIT				1
# define TRANSPARENT		0x0000FF00
# define CROSSHAIR			SDL_SYSTEM_CURSOR_CROSSHAIR
# define ARROW				SDL_SYSTEM_CURSOR_ARROW
# define PAKOMSA			"Your core file seems invalid. Reinstall the game"
# define COREBROKEN			"Core seems to be broken, delete your core.dn3d"
# define CHANGELVL			"Press enter to start next level"
# define ENDGAME			"Congratulation, you finished the game!press enter"
# define WSR				w->stopread
# define SCENAR_1			"Your beloved dog Rex was kidnapped,"
# define SCENAR_2			"     you need to find him !"
# define SCENAR_3			"  Who the hell are these guys ?!  "
# define SCENAR_4			"  They don't seem to mess around "
# define SCENAR_5			"Are they part of an organization ?"
# define SCENAR_6			"   What do they want with Rex ?"
# define SCENAR_7			"       So many of them !"
# define SCENAR_8			" Is Rex such a special dog ?"
# define SCENAR_9			"     Rex is here !"
# define SCENAR_10			"Go get your good boy !"
# define SCENAR_11			"    Hello my Human,"
# define SCENAR_12			" thanks for rescuing me !"
# define SCENAR_13			"  Let's go back home"

#endif
