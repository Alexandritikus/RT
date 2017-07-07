/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:29:19 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 11:52:19 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void		intersect_plane_param(t_intersect *j)
{
	j->u = 0.5 + j->point.x / SIZE;
	j->v = 0.5 + j->point.z / SIZE;
	if (j->normal.z <= j->normal.x && j->normal.z <= j->normal.y)
		j->pu = vector(-j->normal.y, j->normal.x, 0.0);
	else if (j->normal.y <= j->normal.x)
		j->pu = vector(-j->normal.z, 0, j->normal.x);
	else
		j->pu = vector(0, -j->normal.z, j->normal.y);
	j->pv = vector_cross(j->normal, j->pu);
}

bool		intersect_plane(t_object *plane, t_ray ray, t_intersect *j)
{
	double	denom;
	double	size;

	j->normal = vector(0.0, 1.0, 0.0);
	denom = vector_dot(j->normal, ray.direction);
	if (fabs(denom) < DBL_EPSILON)
		return (false);
	j->distance = vector_dot(j->normal,
					vector_sub(vector_zero(), ray.origin)) / denom;
	if (j->distance < 0)
		return (false);
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	size = SIZE / 2.0;
	if (j->point.x < -size || j->point.x > size)
		return (false);
	if (j->point.z < -size || j->point.z > size)
		return (false);
	j->is_inter = true;
	j->obj = plane;
	j->ray = ray;
	return (true);
}
