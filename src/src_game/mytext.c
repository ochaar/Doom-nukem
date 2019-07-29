/*BIG42HEADER*/

#include "doom.h"

void		ft_putmychar(t_env *w, int i, int *xmain, int *ymain)
{
	int		print;
	int		c;
	int		x;
	int		y;

	print = 0;
	x = *xmain;
	y = *ymain;
	if (w->txt.text[i] == '\n')
	{
		print = 1;
		*xmain = w->txt.x;
		*ymain = *ymain + w->ascii[0].h + 5;
	}
	else if (w->txt.text[i] == '\t')
	{
		print = 1;
		c = 41;
		safe_char_to_screen(w, w->ascii[c], x, y);
		safe_char_to_screen(w, w->ascii[c], x + w->ascii[0].w, y);
		safe_char_to_screen(w, w->ascii[c], x + 2 * w->ascii[0].w, y);
		*xmain = *xmain + 3 * w->ascii[0].w;
	}
	else if (w->txt.text[i] == ',')
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
	else if (w->txt.text[i] == '^')
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
	else if (w->txt.text[i] == '%')
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
		print = 1;
	if (print == 0)
	{
		safe_char_to_screen(w, w->ascii[c], x, y);
		*xmain = *xmain + w->ascii[0].w;
	}
}

void		type_s(t_env *w)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = w->txt.x;
	y = w->txt.y;
	while (w->txt.text[i] != '\0')
	{
		ft_putmychar(w, i, &x, &y);
		i++;
	}
	w->txtnxtline.x = w->txt.x;
	w->txtnxtline.y = y + w->ascii[0].h + 5;
	w->txtnxtto.x = x;
	w->txtnxtto.y = y;
}

t_text		type_set(int x, int y, char *s, Uint32 color)
{
	t_text	txt;

	txt.x = x;
	txt.y = y;
	txt.text = s;
	txt.color = color;
	return (txt);
}

void		type_str(t_env *w, t_dot dot, char *s, Uint32 color)
{
	if (w->asciichk == ASCIINB)
	{
		w->txt = type_set(dot.x, dot.y, s, color);
		type_s(w);
	}
}
