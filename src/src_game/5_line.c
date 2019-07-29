/*BIG42HEADER*/

#include "doom.h"

void octant_1(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dy;
		if (e < 0)
		{
			norm.y1++;
			e = e + dx;
		}
		norm.x1++;
	}
}

void octant_2(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dx;
		if (e < 0)
		{
			norm.x1++;
			e = e + dy;
		}
		norm.y1++;
	}
}

void octant_3(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dx;
		if (e <= 0)
		{
			norm.x1--;
			e = e + dy;
		}
		norm.y1++;
	}
}

void octant_4(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dy;
		if (e >= 0)
		{
			norm.y1++;
			e = e + dx;
		}
		norm.x1--;
	}
}

void octant_5(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dy;
		if (e >= 0)
		{
			norm.y1--;
			e = e + dx;
		}
		norm.x1--;
	}
}

void octant_6(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e - dx;
		if (e >= 0)
		{
			norm.x1--;
			e = e + dy;
		}
		norm.y1--;
	}
}

void octant_7(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (norm.y1 != norm.y2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dx;
		if (e > 0)
		{
			norm.x1++;
			e = e + dy;
		}
		norm.y1--;
	}
}

void octant_8(t_vect norm, t_env *w, Uint32 color)
{
	int dx;
	int dy;
	int e;

	dx = norm.dx;
	dy = norm.dy;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (norm.x1 != norm.x2)
	{
		set_txtr_pix(w, norm.x1, norm.y1, color);
		e = e + dy;
		if (e < 0)
		{
			norm.y1--;
			e = e + dx;
		}
		norm.x1++;
	}
}


void crux_x(int x1, int y1, int x2, t_env *w, Uint32 color)
{
	int dx;

	dx = x2 - x1;
	if (dx > 0)
	{
		while (x1 != x2)
		{
			set_txtr_pix(w, x1, y1, color);
			x1++;
		}
	}
	else
	{
		while (x1 != x2)
		{
			set_txtr_pix(w, x1, y1, color);
			x1--;
		}
	}
}

void crux_y(int x1, int y1, int y2, t_env *w, Uint32 color)
{
	int dy;

	dy = y2 - y1;
	if (dy > 0)
	{
		while (y1 != y2)
		{
			set_txtr_pix(w, x1, y1, color);
			y1++;
		}
	}
	else
	{
		while (y1 != y2)
		{
			set_txtr_pix(w, x1, y1, color);
			y1--;
		}
	}
}

void crux(t_vect norm, t_env *w, Uint32 color)
{
	if (norm.dy == 0)
		crux_x(norm.x1, norm.y1, norm.x2, w, color);
	if (norm.dx == 0)
		crux_y(norm.x1, norm.y1, norm.y2, w, color);
}

void vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color)
{
	t_vect norm;

	norm.x1 = p1.x;
	norm.y1 = p1.y;
	norm.x2 = p2.x;
	norm.y2 = p2.y;
	norm.dx	= p2.x - p1.x;
	norm.dy = p2.y - p1.y;
	if (norm.dx == 0 || norm.dy == 0)
		crux(norm, w, color);
	if (norm.dx > 0 && norm.dy > 0 && norm.dx >= norm.dy)
		octant_1(norm, w, color);
	if (norm.dx > 0 && norm.dy > 0 && norm.dx < norm.dy)
		octant_2(norm, w, color);
	if (norm.dx < 0 && norm.dy > 0 && -norm.dx < norm.dy)
		octant_3(norm, w, color);
	if (norm.dx < 0 && norm.dy > 0 && -norm.dx >= norm.dy)
		octant_4(norm, w, color);
	if (norm.dx < 0 && norm.dy < 0 && norm.dx <= norm.dy)
		octant_5(norm, w, color);
	if (norm.dx < 0 && norm.dy < 0 && norm.dx > norm.dy)
		octant_6(norm, w, color);
	if (norm.dx > 0 && norm.dy < 0 && norm.dx < -norm.dy)
		octant_7(norm, w, color);
	if (norm.dx > 0 && norm.dy < 0 && norm.dx >= -norm.dy)
		octant_8(norm, w, color);
}
