/*BIG42HEADER*/

#include "doom.h"

void		recap_sector_general(t_map m, int i)
{
	ft_putstr("sector\t");
	ft_putnbr(i);
	ft_putstr("\t: wall count\t\t  = ");
	ft_putnbrendl(m.sector[i].wall_count);
	ft_putstr("sector\t");
	ft_putnbr(i);
	ft_putstr("\t: floor height\t\t  = ");
	ft_putnbrendl((int)m.sector[i].wall_count);
	ft_putstr("sector\t");
	ft_putnbr(i);
	ft_putstr("\t: ceiling height\t  = ");
	ft_putnbrendl((int)m.sector[i].wall_count);
	ft_putendl("------------------------------------");
}

void		recap_sector_dots(t_map m, int i)
{
	int		j;

	j = 0;
	while (j < m.sector[i].wall_count)
	{
		ft_putstr("sector\t");
		ft_putnbr(i);
		ft_putstr("\t: dot\t");
		ft_putnbr(j);
		ft_putstr(" :\t\tx = ");
		ft_putnbrendl((int)m.sector[i].dot[j].x);
		ft_putstr("sector\t");
		ft_putnbr(i);
		ft_putstr("\t: dot\t");
		ft_putnbr(j);
		ft_putstr(" :\t\ty = ");
		ft_putnbrendl((int)m.sector[i].dot[j].x);
		j++;
	}
	ft_putendl("------------------------------------");
}

void		recap_sector_network(t_map m, int i)
{
	int		j;

	j = 0;
	while (j < m.sector[i].wall_count)
	{
		ft_putstr("sector\t");
		ft_putnbr(i);
		ft_putstr("\t: network ");
		ft_putnbr(j);
		ft_putstr("\t\t  = ");
		ft_putnbrendl(m.sector[i].network[j]);
		j++;
	}
	ft_putendl("------------------------------------");
}

void		recap_sector(t_map m, int i)
{
	recap_sector_general(m, i);
	recap_sector_dots(m, i);
	recap_sector_network(m, i);
	ft_putendl("************************************");
}
