/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius_add2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:54:43 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:00:39 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static int	dblsgn(double x)
{
	if (x < -DBL_EPSILON)
		return (-1);
	return (x > DBL_EPSILON);
}

int			inside(t_vec h)
{
	double	t;
	double	s;

	t = atan2(h.y, h.x);
	if (dblsgn(sin(t / 2)) != 0)
		s = h.z / sin(t / 2);
	else
		s = dblsgn(cos(t)) ? (h.x / cos(t) - SIZE) / cos(t / 2) :
			(h.y / sin(t) - SIZE) / cos(t / 2);
	h.x -= (SIZE + s * cos(t / 2)) * cos(t);
	h.y -= (SIZE + s * cos(t / 2)) * sin(t);
	h.z -= s * sin(t / 2);
	if (dblsgn(h.x * h.x + h.y * h.y + h.z * h.z))
		return (0);
	return (s >= -1 && s <= 1);
}
