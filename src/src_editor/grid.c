/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:50:55 by abechet           #+#    #+#             */
/*   Updated: 2019/06/05 10:51:08 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    draw_grid(t_env *w, t_win *win)
{
    int     i;
    int     j;
    int     x;
    int     y;
    (void)win;
    i = 0;
    j = 0;
    x = 0;
    y = 0;
    while (j < WIN_Y * 10)
    {
        i = 0;
        x = 0;
        while (i < WIN_X * 10)
        {
            // if (i % 100 == 0 || j % 100 == 0)
            //  set_txtr_pix(w, i, j, 0xFF9dfcf6);
            // else if (i % 50 == 0 || j % 50 == 0)
            //  set_txtr_pix(w, i, j, 0xFFb08411);
            // else
                set_txtr_pix(w, i, j, 0xFF36E2D7);
            i += 10;
            x++;
        }
        j += 10;
        y++;
    }
    i = 0;
    j = 0;
    while (i < WIN_Y)
    {
        j = 0;
        while (j < WIN_X)
        {
            set_txtr_pix(w, j, i, 0xFF113d3a);
            j++;
        }
        i += 50;
    }
    i = 0;
    j = 0;
    while (i < WIN_Y)
    {
        j = 0;
        while (j < WIN_X)
        {
            set_txtr_pix(w, i, j, 0xFF113d3a);
            j++;
        }
        i += 50;
    }
}

