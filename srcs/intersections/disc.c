/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:08:06 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 11:51:54 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void		intersect_disc_param(t_ray ray, t_intersect *j)
{
	j->normal = (vector_dot(ray.origin, j->normal) < 0) ?
				vector_mult_d(j->normal, -1) : j->normal;
	j->u = j->point.x / (2.0 * RADIUS) + 0.5;
	j->v = j->point.y / (2.0 * RADIUS) + 0.5;
}

bool		intersect_disc(t_object *disc, t_ray ray, t_intersect *j)
{
	double	denom;

	j->normal = vector(0.0, 0.0, 1.0);
	denom = vector_dot(j->normal, ray.direction);
	if (fabs(denom) < DBL_EPSILON)
		return (false);
	j->distance = vector_dot(j->normal,
					vector_sub(vector_zero(), ray.origin)) * (1 / denom);
	if (j->distance < 0)
		return (false);
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	if (vector_dot(j->point, j->point) > RADIUS * RADIUS)
		return (false);
	j->is_inter = true;
	j->obj = disc;
	j->ray = ray;
	return (true);
}
