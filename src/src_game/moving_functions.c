/*BIG42HEADER*/

#include "doom.h"
// http://peroxide.dk/papers/collision/collision.pdf
// http://www.peroxide.dk/download/tutorials/tut10/pxdtut10.html
// https://wildbunny.co.uk/blog/2011/03/25/speculative-contacts-an-continuous-collision-engine-approach-part-1/
// https://stackoverflow.com/questions/1945632/2d-ball-collisions-with-corners
t_coor  trymapcorner(t_coor player, t_coor speed, t_dot dot)
{
    double len;
    double nx;
    double ny;
    t_coor ret;
    double projection;
    nx = player.x - dot.x;
    ny = player.y - dot.y;
    len = sqrt(nx * nx + ny * ny);
    if (len < 1)
        printf("%f\n", len);
    nx /= len;
    ny /= len;
    projection = speed.x * nx + speed.y * ny;
    ret.x = speed.x - 2 * projection * nx;
    ret.y = speed.y - 2 * projection * ny;
    if (len < 1)
        return (ret);
    else
        return (speed);
}

void		get_height(t_map *m)
{
	int tmp;

	tmp = m->sector[m->player.sector].ceiling - m->sector[m->player.sector].floor;
	if (m->player.stance == 0)
	{
		if (tmp < STAND)
		{
			if (tmp > CROUCH)
			{
				if (m->player.height < CROUCH)
					m->player.height = m->player.height + 0.1;
				else
					m->player.height = CROUCH;
			}
			else
				m->player.height = CRAWL;
		}
		else if (m->player.height < CROUCH - 4)
			m->player.height = m->player.height + 0.1;
		else if (m->player.height < STAND - 0.2)
			m->player.height = m->player.height + 0.3;
		else
			m->player.height = STAND;
	}
	if (m->player.stance == 1)
	{
		if (tmp < CROUCH)
			m->player.height = CRAWL;
		else if (m->player.height < CROUCH - 4)
			m->player.height = m->player.height + 0.1;
		else if (m->player.height < CROUCH - 0.2)
			m->player.height = m->player.height + 0.3;
		else
			m->player.height = CROUCH;
	}
	if (m->player.stance == 2)
		m->player.height = CRAWL;
	m->player.ground = !m->player.fall;
}

void		is_falling(t_map *m)
{
	double	nxtz;

	if (m->player.fall == 1)
	{
		m->player.move_speed.z = m->player.move_speed.z - m->gravity;
		nxtz = m->player.coor.z + m->player.move_speed.z;
		if (m->player.move_speed.z < 0 && nxtz < m->sector[m->player.sector].floor + m->player.height)
		{
			m->player.coor.z = m->sector[m->player.sector].floor + m->player.height;
			if (m->player.move_speed.z <= -1.7  && m->god_mod != 1)
				m->player.hp = m->player.hp - (10 * -m->player.move_speed.z * -m->player.move_speed.z);
			m->player.move_speed.z = 0;
			m->player.fall = 0;
			m->player.ground = 1;
			m->player.jump = 0;
		}
		else if (m->player.move_speed.z > 0 && nxtz > m->sector[m->player.sector].ceiling)
		{
			m->player.move_speed.z = 0;
			m->player.fall = 1;
		}
		if (m->player.fall == 1)
		{
			m->player.coor.z = m->player.coor.z + m->player.move_speed.z;
			m->player.moving = 1;
		}
	}
}

void 		slow_down(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] || w->inkeys[SDL_SCANCODE_S]
	|| w->inkeys[SDL_SCANCODE_A] || w->inkeys[SDL_SCANCODE_D])
		m->player.press = 1;
	else
		m->player.press = 0;
	if (m->player.press == 1)
		m->player.accel = 0.4;
	else
		m->player.accel = 0.2;
	m->player.move_speed.x = m->player.move_speed.x * (1 - m->player.accel) + m->player.move_speedless.x * m->player.accel;
	m->player.move_speed.y = m->player.move_speed.y * (1 - m->player.accel) + m->player.move_speedless.y * m->player.accel;
	if (m->player.press == 1)
		m->player.moving = 1;
	else
		m->player.moving = 0;
	m->player.move_speedless.x = 0.f;
	m->player.move_speedless.y = 0.f;
}

int			is_on_a_map_dot(t_map *m, int sector)
{
	t_intersect i;
	double		r1;
	double		r2;

	i.mem = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + (m->player.move_speed.x * 5);
	i.y2 = m->player.coor.y + (m->player.move_speed.y * 5);
	//printf("%f,%f\n", (m->player.move_speed.x * 12), (m->player.move_speed.y * 12));
	while (i.mem < m->sector[sector].wall_count)
	{
		i.x3 = m->sector[sector].dot[i.mem].x;
		i.y3 = m->sector[sector].dot[i.mem].y;
		r1 = (i.x3 - i.x1) * (i.y2 - i.y1);
		r2 = (i.y3 - i.y1) * (i.x2 - i.x1);
		if ((int)r1 == (int)r2)
		{
			if ((i.x3 > vmin(i.x1, i.x2) && i.x3 < vmax(i.x1, i.x2))
				|| (i.y3 > vmin(i.y1, i.y2) && i.y3 < vmax(i.y1, i.y2)))
				return (-1);
		}
		i.mem++;
	}
	return (0);
}

int			is_next_to_a_dot(t_map *m)
{
	t_intersect	i;
	double		slope;
	double		diffx;
	double		diffy;
	double		dist;
	double		dist_min;
	int			dot_mem;

	i.mem = 0;
	dist_min = 0;
	slope = 0;
	diffx = 0;
	diffy = 0;
	dist = 0;
	dot_mem = 0;
	i.x1 = m->player.coor.x + m->player.move_speed.x;
	i.y1 = m->player.coor.y + m->player.move_speed.y;
	while (i.mem < m->dots_count)
	{
		i.x2 = m->dot[i.mem].x;
		i.y2 = m->dot[i.mem].y;
		slope = (i.y2 - i.y1) / (i.x2 - i.x1);
		diffx = (i.x1 - i.x2);
		diffy = (i.y1 - i.y2);
		if (vabs(diffx) > vabs(diffy))
			dist = vabs(diffx / cos(slope));
		else
			dist = vabs(diffy / sin(slope));
		if (dist_min == 0)
		{
			dist_min = dist;
			dot_mem = i.mem;
		}
		else if (dist < dist_min)
		{
			dist_min = dist;
			dot_mem = i.mem;
		}
		i.mem++;
	}
	slope = atan2((i.y1 - m->dot[dot_mem].y), (i.x1 - m->dot[dot_mem].x));
	if (dist_min < 0.5)
		m->player.move_speed = trymapcorner(m->player.coor, m->player.move_speed, m->dot[dot_mem]);
	return (0);
}

void move_player(double dx, double dy, t_map *m)
{
	int			s;
	t_intersect	i;
	t_coor		coor;
	

	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + dx;
	i.y2 = m->player.coor.y + dy;
	s = 0;
	while (s < m->sector[m->player.sector].wall_count)
	{
		i.x3 = m->sector[m->player.sector].dot[s].x;
		i.y3 = m->sector[m->player.sector].dot[s].y;
		i.x4 = m->sector[m->player.sector].dot[s + 1].x;
		i.y4 = m->sector[m->player.sector].dot[s + 1].y;
		coor.x = i.x2;
		coor.y = i.y2;
		if(m->sector[m->player.sector].network[s] >= 0 && intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) < 0)
		{
			m->player.sector = m->sector[m->player.sector].network[s];
			// is_next_to_a_dot(m);
			// if (is_on_a_map_dot(m) == -1)
			// {
			// 	dx = 0;
			// 	dy = 0;
			// }
			break ;
		}
		s++;
	}
	m->player.coor.x = m->player.coor.x + dx;
	m->player.coor.y = m->player.coor.y + dy;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		is_moving(t_map *m)
{
	int			s;
	t_intersect	i;
	t_coor		coor;

	s = 0;
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + m->player.move_speed.x;
	i.y2 = m->player.coor.y + m->player.move_speed.y;
	coor.x = i.x2;
	coor.y = i.y2;
	i.dx = m->player.move_speed.x;
	i.dy = m->player.move_speed.y;
	while (s < m->sector[m->player.sector].wall_count)
	{
		i.x3 = m->sector[m->player.sector].dot[s].x;
		i.y3 = m->sector[m->player.sector].dot[s].y;
		i.x4 = m->sector[m->player.sector].dot[s + 1].x;
		i.y4 = m->sector[m->player.sector].dot[s + 1].y;
		if (intersectbox(i) && pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->player.hole_low = 9e9;
			m->player.hole_high = -9e9;
			if (m->sector[m->player.sector].network[s] >= 0)
			{
				m->player.hole_low = vmax(m->sector[m->player.sector].floor, m->sector[m->sector[m->player.sector].network[s]].floor);
				m->player.hole_high = vmin(m->sector[m->player.sector].ceiling, m->sector[m->sector[m->player.sector].network[s]].ceiling);
			}
			if (m->player.hole_high < m->player.coor.z + HEADMARGIN
			|| m->player.hole_low > m->player.coor.z - m->player.height + KNEEH)
			{
				i.xd = m->sector[m->player.sector].dot[s + 1].x - m->sector[m->player.sector].dot[s].x;
				i.yd = m->sector[m->player.sector].dot[s + 1].y - m->sector[m->player.sector].dot[s].y;
				m->player.move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->player.move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->player.moving = 0;
			}
			if (is_on_a_map_dot(m, m->player.sector) == -1)
			{
				m->player.move_speed.x = 0;
				m->player.move_speed.y = 0;
			}
		}
		s++;
	}	
	// is_next_to_a_dot(m);
	move_player(m->player.move_speed.x, m->player.move_speed.y, m);
	m->player.fall = 1;
}
