/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:15:31 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:15:34 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	cubic_up(t_cubic_tmp tmp, double c[3], double roots[3])
{
	double		w_m;
	double		w_p;

	tmp.w = sqrt(tmp.w);
	if (tmp.v < 0)
	{
		w_m = tmp.w - tmp.v;
		roots[0] = cbrt(w_m / 2.0) - (tmp.u * cbrt(2.0 / w_m) + c[0]) / 3.0;
	}
	else
	{
		w_p = tmp.w + tmp.v;
		roots[0] = -cbrt(w_p / 2.0) + (tmp.u * cbrt(2.0 / w_p) - c[0]) / 3.0;
	}
}

static void	cubic_down(t_cubic_tmp tmp, double c[3], double roots[3])
{
	tmp.s = sqrt(-tmp.u / 3);
	if (tmp.s != 0)
	{
		tmp.t = -tmp.v / (2.0 * tmp.s * tmp.s * tmp.s);
		tmp.k = acos(tmp.t) / 3.0;
		tmp.sink = sin(tmp.k);
		tmp.cosk = cos(tmp.k);
	}
	else
	{
		tmp.cosk = 0;
		tmp.sink = 0;
	}
	tmp.p_3 = c[0] / 3.0;
	roots[0] = 2.0 * tmp.s * tmp.cosk - tmp.p_3;
	roots[1] = 2.0 * tmp.s * (-tmp.cosk + SQRT3 * tmp.sink) / 2.0 - tmp.p_3;
	roots[2] = 2.0 * tmp.s * (-tmp.cosk - SQRT3 * tmp.sink) / 2.0 - tmp.p_3;
}

int			cubic_roots(double c[3], double roots[3])
{
	t_cubic_tmp	tmp;

	tmp.u = c[1] - c[0] * c[0] / 3.0;
	tmp.v = c[2] - c[0] * c[1] / 3 + 2 * c[0] * c[0] * c[0] / 27;
	tmp.w = (4 * tmp.u * tmp.u * tmp.u) / 27 + tmp.v * tmp.v;
	if (tmp.w > 0)
	{
		cubic_up(tmp, c, roots);
		return (1);
	}
	else
	{
		cubic_down(tmp, c, roots);
		return (3);
	}
}
