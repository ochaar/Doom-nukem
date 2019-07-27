/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:21:24 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/25 12:58:42 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	affichage_set_str(t_env *w)
{
	t_dot	dot;

	dot.y = 10;
	if (w->window_mode_menu == 0)
	{
		dot.x = WIDTH - 215;
		type_str(w, dot, "FULL SCREEN", 0x12FEA800);
	}
	else
	{
		dot.x = WIDTH - 170;
		type_str(w, dot, "WINDOWED", 0x12FEA800);
	}
	dot.y += 50;
	if (w->window_res_menu == 0)
	{
		dot.x = WIDTH - 203;
		type_str(w, dot, "1024 x 576", 0x12FEA800);
	}
	else
	{
		dot.x = WIDTH - 220;
		type_str(w, dot, "1920 x 1080", 0x12FEA800);
	}
}

void	aff_menu_screen_2(t_env *w, char *start, t_dot dot)
{
	if (w->menu.j == 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EDITOR\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j > 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EXIT", 0xFF78F7);
	}
}

void	aff_menu_screen_1(t_env *w, char *start, t_dot dot)
{
	if (w->menu.j <= 1)
	{
		type_str(w, dot, start, 0xFF78F7);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> MAPS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 3)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> SETTINGS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
}

void	menu_screen(t_env *w)
{
	char	*start;
	t_dot	dot;

	dot = fill_t_dot(WIDTH / 2 - 50, 140);
	if (w->m->newgame == 1)
	{
		if (w->menu.j == 1)
			start = strdup_check(w, "> NEW GAME\n");
		else
			start = strdup_check(w, "NEW GAME\n");
	}
	else
	{
		if (w->menu.j == 1)
			start = strdup_check(w, "> CONTINUE\n");
		else
			start = strdup_check(w, "CONTINUE\n");
	}
	main_pic(w, 1);
	if (w->menu.j < 4)
		aff_menu_screen_1(w, start, dot);
	else
		aff_menu_screen_2(w, start, dot);
	free(start);
}
