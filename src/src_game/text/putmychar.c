/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:21:16 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/24 22:21:18 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	convert3(t_env *w, int i, int c, int *print)
{
	if (w->txt.text[i] == '%')
		c = 58;
	else if (w->txt.text[i] == '|')
		c = 59;
	else if (w->txt.text[i] == '+')
		c = 60;
	else if (w->txt.text[i] == '/')
		c = 61;
	else if (w->txt.text[i] == '*')
		c = 62;
	else if (w->txt.text[i] == '~')
		c = 63;
	else if (w->txt.text[i] == '\'')
		c = 64;
	else if (w->txt.text[i] == ';')
		c = 65;
	else if (w->txt.text[i] == '_')
		c = 66;
	else if (ft_isdigit(w->txt.text[i]) == 1)
		c = (int)(w->txt.text[i] - 48);
	else if (ft_isalpha(w->txt.text[i]) == 1)
		c = (int)(ft_toupper(w->txt.text[i]) - 55);
	else
		*print = 1;
	return (c);
}

static int	convert2(t_env *w, int i, int c, int *print)
{
	if (w->txt.text[i] == '^')
		c = 47;
	else if (w->txt.text[i] == '>')
		c = 48;
	else if (w->txt.text[i] == '<')
		c = 49;
	else if (w->txt.text[i] == ']')
		c = 50;
	else if (w->txt.text[i] == '[')
		c = 51;
	else if (w->txt.text[i] == '#')
		c = 52;
	else if (w->txt.text[i] == '$')
		c = 53;
	else if (w->txt.text[i] == '=')
		c = 54;
	else if (w->txt.text[i] == '-')
		c = 55;
	else if (w->txt.text[i] == ')')
		c = 56;
	else if (w->txt.text[i] == '(')
		c = 57;
	else
		c = convert3(w, i, c, print);
	return (c);
}

static int	convert(t_env *w, int i, int c, int *print)
{
	if (w->txt.text[i] == ',')
		c = 36;
	else if (w->txt.text[i] == ':')
		c = 37;
	else if (w->txt.text[i] == '!')
		c = 38;
	else if (w->txt.text[i] == '?')
		c = 39;
	else if (w->txt.text[i] == '.')
		c = 40;
	else if (w->txt.text[i] == ' ')
		c = 41;
	else if (w->txt.text[i] == '\"')
		c = 42;
	else if (w->txt.text[i] == '}')
		c = 43;
	else if (w->txt.text[i] == '{')
		c = 44;
	else if (w->txt.text[i] == '@')
		c = 45;
	else if (w->txt.text[i] == '\\')
		c = 46;
	else
		c = convert2(w, i, c, print);
	return (c);
}

static int	set_pointers_and_print(int *x, int *y, int *xmain, int *ymain)
{
	*x = *xmain;
	*y = *ymain;
	return (0);
}

void		ft_putmychar(t_env *w, int i, int *xmain, int *ymain)
{
	int		print;
	int		c;
	int		x;
	int		y;

	print = set_pointers_and_print(&x, &y, xmain, ymain);
	c = print;
	if (w->txt.text[i] == '\n')
	{
		print = 1;
		*xmain = w->txt.x;
		*ymain = *ymain + w->ascii[0].h + 5;
	}
	else if (w->txt.text[i] == '\t')
	{
		print = 1;
		*xmain = *xmain + 3 * w->ascii[0].w;
	}
	else
		c = convert(w, i, c, &print);
	if (print == 0)
	{
		safe_char_to_screen(w, w->ascii[c], x, y);
		*xmain = *xmain + w->ascii[0].w;
	}
}
