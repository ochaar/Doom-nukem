/*BIG42HEADER*/

#include "doom.h"

void	set_txtr_pix(t_env *w, int x, int y, Uint32 color)
{
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
		w->pix[y * WIDTH + x] = color;
}

void	set_txtr_dot(t_env *w, int x, int y, Uint32 color)
{
	int		i;

	i = 0;
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		w->pix[y * WIDTH + x] = color;
		while (i < 3)
		{
			if (y - i >= 0)
				w->pix[(y - i) * WIDTH + x] = color;
			if (x - i >= 0)
				w->pix[y * WIDTH + (x - i)] = color;
			if (y + i < HEIGHT)
				w->pix[(y + i) * WIDTH + x] = color;
			if (x + i < WIDTH)
				w->pix[y * WIDTH + (x + i)] = color;
			i++;
		}
	}
}

void	draw_mini_map(t_env *w, t_map *m)
{
	t_work	work;
	int		sector;
	int		point;

	work.p1.x = WIDTH - (WIDTH / 2) / 3;
	work.p1.y = HEIGHT - (HEIGHT / 2 - 1) / 3;
	work.p2.x = (work.p1.x);
	work.p2.y = (work.p1.y - 3);
	set_txtr_dot(w, work.p1.x, work.p1.y + 1, 0x12BF3030);
	vect_ab(work.p1, work.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			work.v1.x = (m->sector[sector].dot[point].x - PL_X);
			work.v1.y = (m->sector[sector].dot[point].y - PL_Y);
			work.v2.x = (m->sector[sector].dot[point + 1].x - PL_X);
			work.v2.y = (m->sector[sector].dot[point + 1].y - PL_Y);
			work.t1.x = WIDTH - ((work.v1.x * PL_AS - work.v1.y * PL_AC) * 10 + (WIDTH / 2)) / 3;
			work.t1.y = HEIGHT - ((work.v1.x * PL_AC + work.v1.y * PL_AS) * 10 + (HEIGHT / 2)) / 3;
			work.t2.x = WIDTH - ((work.v2.x * PL_AS - work.v2.y * PL_AC) * 10 + (WIDTH / 2)) / 3;
			work.t2.y = HEIGHT - ((work.v2.x * PL_AC + work.v2.y * PL_AS) * 10 + (HEIGHT / 2)) / 3;
			if (m->sector[sector].network[point] < 0)
				vect_ab(work.t1, work.t2, w, 0x12FF0000);
			point++;
		}
		sector++;
	}
}

void	draw_map(t_env *w, t_map *m)
{
	t_work	work;
	int		sector;
	int		point;

	clean_render(w, 0x12CECECE);
	work.p1.x = WIDTH / 2;
	work.p1.y = HEIGHT / 2 - 1;
	work.p2.x = work.p1.x;
	work.p2.y = work.p1.y - 9;
	set_txtr_dot(w, work.p1.x, work.p1.y + 1, 0x12BF3030);
	vect_ab(work.p1, work.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			work.winwidth = WIDTH;
			work.winheight = HEIGHT;
			work.v1.x = (m->sector[sector].dot[point].x - PL_X);
			work.v1.y = (m->sector[sector].dot[point].y - PL_Y);
			work.v2.x = (m->sector[sector].dot[point + 1].x - PL_X);
			work.v2.y = (m->sector[sector].dot[point + 1].y - PL_Y);
			work.t1.x = -(work.v1.x * PL_AS - work.v1.y * PL_AC) * 10 + (work.winwidth / 2);
			work.t1.y = -(work.v1.x * PL_AC + work.v1.y * PL_AS) * 10 + (work.winheight / 2);
			work.t2.x = -(work.v2.x * PL_AS - work.v2.y * PL_AC) * 10 + (work.winwidth / 2);
			work.t2.y = -(work.v2.x * PL_AC + work.v2.y * PL_AS) * 10 + (work.winheight / 2);
			if (m->sector[sector].network[point] < 0)
				vect_ab(work.t1, work.t2, w, 0x12FF0000);
			point++;
		}
		sector++;
	}
}
