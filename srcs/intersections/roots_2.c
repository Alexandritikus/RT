/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:15:17 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:15:21 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	ini_polish(double c[3], double d, t_polish_tmp *tmp)
{
	tmp->lastx = HUGE;
	tmp->lasty = HUGE;
	tmp->cs[0] = c[0];
	tmp->cs[1] = c[1];
	tmp->cs[2] = c[2];
	tmp->cs[3] = d;
}

static void	polish_root_2(int degree, t_polish_tmp *tmp)
{
	int j;

	j = -1;
	tmp->y = 1;
	tmp->dydx = 0;
	while (++j < degree)
	{
		tmp->dydx = tmp->dydx * tmp->x + tmp->y;
		tmp->y *= tmp->x;
		tmp->y += tmp->cs[j];
	}
}

double		polish_root(int degree, double c[3], double d, double root)
{
	t_polish_tmp	tmp;
	int				i;

	ini_polish(c, d, &tmp);
	i = -1;
	tmp.x = root;
	while (++i < 3)
	{
		polish_root_2(degree, &tmp);
		if (tmp.dydx == 0)
			break ;
		if (fabs(tmp.y) > fabs(tmp.lasty))
		{
			tmp.x = tmp.lastx;
			break ;
		}
		tmp.lasty = tmp.y;
		tmp.dx = tmp.y / tmp.dydx;
		tmp.lastx = tmp.x;
		tmp.x -= tmp.dx;
		if (tmp.lastx == tmp.x)
			break ;
	}
	return (tmp.x);
}
