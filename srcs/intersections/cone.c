/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:55:47 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:13:03 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	cone_disc(t_ray ray, t_intersect *j, double z1, double z2)
{
	double	t3;
	int		signz1;
	int		signz2;

	t3 = (-HEIGHT - ray.origin.z) / ray.direction.z;
	signz1 = ((z1 - -HEIGHT) > 0) ? 1 : 0;
	signz2 = ((z2 - -HEIGHT) > 0) ? 1 : 0;
	if (signz1 != signz2 && t3 > 0 && t3 < j->distance)
	{
		j->distance = t3;
		j->point = vector_add(ray.origin,
					vector_mult_d(ray.direction, j->distance));
		j->normal = vector(0.0, 0.0, -HEIGHT);
	}
}

static void	cone_body(t_ray ray, t_intersect *j, t_root roots, size_t num_r)
{
	double	t2;
	double	z1;
	double	z2;

	t2 = (num_r == 2) ? roots.roots_2[1] : INFINITY;
	if (roots.roots_2[0] > 0 || t2 > 0)
	{
		z1 = ray.origin.z + roots.roots_2[0] * ray.direction.z;
		z2 = ray.origin.z + t2 * ray.direction.z;
		j->distance = (z1 < 0.0 && z1 > -HEIGHT && roots.roots_2[0] > 0) ?
											roots.roots_2[0] : j->distance;
		if (z2 < 0.0 && z2 > -HEIGHT && t2 > 0 && t2 < j->distance)
			j->distance = t2;
		if (!isinf(j->distance))
		{
			j->point = vector_add(ray.origin,
						vector_mult_d(ray.direction, j->distance));
			j->normal = vector(2 * j->point.x, 2 * j->point.y, -2 * j->point.z);
			j->u = acos(vector_dot(vector(j->point.x, j->point.y, 0.0),
						vector(1.0, 0.0, 0.0))) / M_PI;
			j->v = j->point.z / -HEIGHT;
			cone_disc(ray, j, z1, z2);
			j->is_inter = true;
		}
	}
}

bool		intersect_cone(t_object *cone, t_ray ray, t_intersect *j)
{
	t_root	roots;
	int		num_roots;

	roots.a = ray.direction.x * ray.direction.x +
				ray.direction.y * ray.direction.y -
				ray.direction.z * ray.direction.z;
	roots.b = 2 * ray.origin.x * ray.direction.x +
				2 * ray.origin.y * ray.direction.y -
				2 * ray.origin.z * ray.direction.z;
	roots.c = ray.origin.x * ray.origin.x +
				ray.origin.y * ray.origin.y -
				ray.origin.z * ray.origin.z;
	num_roots = quadratic_roots(&roots);
	j->distance = INFINITY;
	j->is_inter = false;
	if (num_roots > 0)
		cone_body(ray, j, roots, num_roots);
	j->obj = cone;
	j->ray = ray;
	return (j->is_inter);
}
