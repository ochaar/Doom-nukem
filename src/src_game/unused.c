// int			is_on_a_dot(t_map *m, int s)
// {
// 	double px, py;
// 	double pnx, pny;
// 	double p1x, p1y;
// 	double p2x, p2y;
// 	double		r1;
// 	double		r2;
// 	double		r3;
// 	double		r4;
// 	double	kac;
// 	double 	kab;
// 	double	kac2;
// 	double 	kab2;
// /* sources	https://www.cap-concours.fr/administratif/culture-disciplinaire/reviser/equations-de-droites-et-systemes-d-equations-lineaires-2_m305
// 			https://www.lucidar.me/fr/mathematics/check-if-a-point-belongs-on-a-line-segment/ */
// 	px = m->player.coor.x;
// 	py = m->player.coor.y;
// 	pnx = m->player.coor.x;
// 	pny = m->player.coor.y;
// 	p1x = m->sector[m->player.sector].dot[s].x;
// 	p1y = m->sector[m->player.sector].dot[s].y;
// 	p2x = m->sector[m->player.sector].dot[s + 1].x;
// 	p2y = m->sector[m->player.sector].dot[s + 1].y;
// 	r1 = (p1x - px) * (pny - py);
// 	r2 = (p1y - py) * (pnx - px);
// 	r3 = (p2x - px) * (pny - py);
// 	r4 = (p2y - py) * (pnx - px);
// 	// printf("p1x:%f,p1y:%f\n", p2x, p2y);
// 	// printf("px:%f,py:%f,pnx:%f,pny:%f\n", px,py,pnx,pny);
// 	if (r1 == r2 || r3 == r4)
// 	{
// /* ----------------------------------------------------------------------- */
// 		// printf("r1:%f,r2:%f,r3:%f,r4:%f\n", r1,r2,r3,r4);
// 		kac = (pnx - px) * (p1x - px) + (pny - py) * (p1y - py);
// 		kab = (pnx - px) * (pnx - px) + (pny - py) * (pny - py);
// 		kac2 = (pnx - px) * (p2x - px) + (pny - py) * (p2y - py);
// 		kab2 = (pnx - px) * (pnx - px) + (pny - py) * (pny - py);
// 		// printf("kac:%f,kab:%f,kac2:%f,kab2:%f\n", kac, kab, kac2, kab2);
// 		// printf("dotx:%f,x1:%f,x2:%f\n", p2x, px, pnx);
// 		// printf("%d\n", m->player.sector);
// 		// ft_putendl("----------------------------------------");
// 		if ((kac > 0 && kac < kab)
// 			|| (kac2 > 0 && kac2 < kab2))
// 			return (-1);
// 		else
// 			return (0);
// 	}
// 	else
// 		return (0);
// }

int			is_on_a_dot(t_map *m, int s)
{
	t_intersect i;
	int		r1;
	int		r2;
	int		r3;
	int		r4;
/* sources	https://www.cap-concours.fr/administratif/culture-disciplinaire/reviser/equations-de-droites-et-systemes-d-equations-lineaires-2_m305
			https://www.lucidar.me/fr/mathematics/check-if-a-point-belongs-on-a-line-segment/ */
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = m->player.coor.x + m->player.move_speed.x;
	i.y2 = m->player.coor.y + m->player.move_speed.y;
	i.x3 = m->sector[m->player.sector].dot[s].x;
	i.y3 = m->sector[m->player.sector].dot[s].y;
	i.x4 = m->sector[m->player.sector].dot[s + 1].x;
	i.y4 = m->sector[m->player.sector].dot[s + 1].y;
	r1 = (i.x3 - i.x1) * (i.y2 - i.y1);
	r2 = (i.y3 - i.y1) * (i.x2 - i.x1);
	r3 = (i.x4 - i.x1) * (i.y2 - i.y1);
	r4 = (i.y4 - i.y1) * (i.x2 - i.x1);
	if (r1 == r2 || r3 == r4)
	{
		// printf("dotx:%f,x1:%f,x2:%f\n", i.x3, i.x1, i.x2);
		// printf("dotx:%f,x1:%f,x2:%f\n", i.x4, i.x1, i.x2);
		// printf("%d\n", m->player.sector);
		ft_putendl("----------------------------------------");
		if ((	i.x3 > vmin(i.x1, i.x2) && i.x3 < vmax(i.x1, i.x2))
			|| (i.y3 > vmin(i.y1, i.y2) && i.y3 < vmax(i.y1, i.y2))
			|| (i.x4 > vmin(i.x1, i.x2) && i.x4 < vmax(i.x1, i.x2))
			|| (i.y4 > vmin(i.y1, i.y2) && i.y4 < vmax(i.y1, i.y2)))
			return (-1);
		else
			return (0);
	}
	else
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
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
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
	// m->player.move_speedless.x += m->player.anglecos / 3;
	// m->player.move_speedless.y += m->player.anglesin / 3;
	slope = atan((i.y1 - m->dot[dot_mem].y) / (i.x1 - m->dot[dot_mem].x));
	// printf("slope:%f,slopecos:%f,slopesin:%f\n", slope, cos(slope), sin(slope));
	if (dist_min < 1)
	{
		m->player.move_speed.x = 0;
		m->player.move_speed.y = 0;
		// m->player.coor.x = m->dot[dot_mem].x + cos(slope)*dist_min;
		// m->player.coor.x = m->dot[dot_mem].y + sin(slope)*dist_min;
		// m->player.move_speed.x = cos(slope)*dist_min;
		// m->player.move_speed.y = sin(slope)*dist_min;
		return (-1);
	}
	// printf("point:%d,dist:%f\n", dot_mem, dist_min);
	return (0);
}
