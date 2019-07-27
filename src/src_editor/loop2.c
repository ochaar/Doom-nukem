/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:09:20 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 13:09:33 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		och4(t_win *win, t_lst *tmp, t_lstlst *tmp2)
{
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp && win->moving == 0)
		{
			if (tmp->x == win->x0 && tmp->y == win->y0)
			{
				win->tmp = tmp;
				win->moving = 1;
			}
			else
				tmp = tmp->next;
		}
		if (win->moving == 1)
		{
			win->tmp->x = win->x2;
			win->tmp->y = win->y2;
			if (tmp2->closed == 1)
				last_is_first(tmp2->head);
		}
		tmp2 = tmp2->next;
	}
}

void		och3(t_win *win, t_lst *tmp, t_lstlst *tmp2, t_lstast *tmp3)
{
	if (win->left_click == 1 && win->mode == 1)
	{
		tmp2 = win->lstlst;
		tmp3 = win->lstast;
		och4(win, tmp, tmp2);
		while (tmp3 && win->moving == 0)
		{
			if (tmp3->x == win->x0 && tmp3->y == win->y0)
			{
				win->tmpasset = tmp3;
				win->moving = 2;
			}
			else
				tmp3 = tmp3->next;
		}
		if (win->moving == 2)
		{
			if (win->tmpasset)
			{
				win->tmpasset->x = win->x2;
				win->tmpasset->y = win->y2;
			}
		}
	}
}

void		och2(t_env *w, t_win *win, t_lstlst *tmp2)
{
	if (win->sector == win->link)
	{
		tmp2 = win->lstlst;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = lstlstnew(w, win);
	}
}

int			och1(t_env *w, t_win *win, t_lstlst *tmp2, int closed)
{
	t_dot	dot;

	win->drawing = 1;
	if (win->lst == NULL)
	{
		dot = fill_t_dot(win->x1, win->y1);
		win->lst = lstnew(w, win, dot, win->sector);
		tmp2 = win->lstlst;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->head = win->lst;
	}
	else
	{
		dot = fill_t_dot(win->x1, win->y1);
		closed = check_list(w, win, win->lst, dot);
	}
	return (closed);
}

void		och(t_env *w, t_win *win, t_lstlst *tmp2, int closed)
{
	if (win->left_click && win->mode == 0)
	{
		if (win->lstlst == NULL)
			win->lstlst = lstlstnew(w, win);
		och2(w, win, tmp2);
		closed = och1(w, win, tmp2, closed);
		if (closed)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->closed = 1;
		}
	}
}
