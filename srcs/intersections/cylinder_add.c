/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:51:22 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 11:51:32 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

t_disc		cyl_disc(t_vec pos, double r)
{
	t_disc	disc;

	disc.pos = pos;
	disc.r = r;
	return (disc);
}

bool		intersect_cyl_disc(t_disc disc, t_ray ray, t_intersect *j)
{
	double	denom;

	j->normal = vector(0.0, 0.0, 1.0);
	denom = vector_dot(j->normal, ray.direction);
	if (fabs(denom) < DBL_EPSILON)
		return (false);
	j->distance = vector_dot(j->normal,
					vector_sub(disc.pos, ray.origin)) * (1 / denom);
	if (j->distance < 0)
		return (false);
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	if (vector_dot(vector_sub(j->point, disc.pos),
				vector_sub(j->point, disc.pos)) > disc.r * disc.r)
		return (false);
	j->is_inter = true;
	return (true);
}
