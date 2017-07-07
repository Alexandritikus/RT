/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:38:05 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/10 11:27:23 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	paraboloid_body(t_ray ray, t_intersect *j, t_root roots, int num_r)
{
	double	t2;
	double	z1;
	double	z2;

	t2 = (num_r == 1) ? INFINITY : roots.roots_2[1];
	if (roots.roots_2[0] > 0 || t2 > 0)
	{
		z1 = ray.origin.z + roots.roots_2[0] * ray.direction.z;
		z2 = ray.origin.z + t2 * ray.direction.z;
		j->distance = (z1 < HEIGHT / 2.0 && z1 > -(HEIGHT / 2.0) &&
		roots.roots_2[0] > 0) ? roots.roots_2[0] : j->distance;
		if (z2 < HEIGHT / 2.0 && z2 > -(HEIGHT / 2.0) &&
												t2 > 0 && t2 < j->distance)
			j->distance = t2;
		if (!isinf(j->distance))
		{
			j->point = vector_add(ray.origin,
			vector_mult_d(ray.direction, j->distance));
			j->normal = vector(2 * j->point.x, 2 * j->point.y,
												-2 * j->point.z);
			j->is_inter = true;
		}
	}
}

bool		intersect_paraboloid(t_object *parab, t_ray ray, t_intersect *j)
{
	t_root	roots;
	int		num_r;
	double	k;

	k = RADIUS;
	roots.a = k * (ray.direction.x * ray.direction.x +
					ray.direction.y * ray.direction.y);
	roots.b = 2 * k * (ray.direction.x * ray.origin.x +
				ray.direction.y * ray.origin.y) - ray.direction.z;
	roots.c = k * (ray.origin.x * ray.origin.x +
				ray.origin.y * ray.origin.y) - ray.origin.z;
	num_r = quadratic_roots(&roots);
	if (num_r > 0)
		paraboloid_body(ray, j, roots, num_r);
	j->ray = ray;
	j->obj = parab;
	return (j->is_inter);
}
