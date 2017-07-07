/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:18:10 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:18:12 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static bool	check_intersection(t_ray ray, t_intersect *j, t_vec e1, t_vec e2)
{
	j->distance = vector_dot(e1, vector_cross(ray.direction, e2));
	if (j->distance > -ACCURACY && j->distance < ACCURACY)
		return (false);
	j->distance = 1.0 / j->distance;
	j->u = j->distance * vector_dot(vector_sub(ray.origin, vector(1, 1, 0)),
					vector_cross(ray.direction, e2));
	if (j->u < 0.0 || j->u > 1.0)
		return (false);
	j->v = j->distance * vector_dot(ray.direction,
					vector_cross(vector_sub(ray.origin, vector(1, 1, 0)), e1));
	if (j->v < 0.0 || j->u + j->v > 1.0)
		return (false);
	j->distance = j->distance * vector_dot(e2,
					vector_cross(vector_sub(ray.origin, vector(1, 1, 0)), e1));
	return (true);
}

bool		intersect_triangle(t_object *triangle, t_ray ray, t_intersect *j)
{
	t_vec	e1;
	t_vec	e2;

	e1 = vector_sub(vector(1, 0, 0), vector(1, 1, 0));
	e2 = vector_sub(vector(0, 1, 0), vector(1, 1, 0));
	if (!check_intersection(ray, j, e1, e2))
		return (false);
	if (j->distance > 0.00001)
	{
		j->point = vector_add(ray.origin,
					vector_mult_vec(vector_one(j->distance), ray.direction));
		j->normal = vector_cross(e1, e2);
		j->is_inter = true;
		j->ray = ray;
		j->obj = triangle;
		return (true);
	}
	return (false);
}
