/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:53:03 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:18:22 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	tube_body(t_ray ray, t_intersect *j, t_root roots,
												size_t num_roots)
{
	double	t2;
	double	z1;
	double	z2;

	t2 = (num_roots == 1) ? INFINITY : roots.roots_2[1];
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
			j->is_inter = true;
	}
}

void		intersect_tube_param(t_ray ray, t_intersect *j)
{
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	j->normal = j->point;
	j->u = acos(vector_dot(vector(j->normal.x, j->normal.y, 0.0),
							vector(1.0, 0.0, 0.0))) / M_PI;
	j->v = j->normal.z + 0.5;
	j->normal.z = 0.0;
}

bool		intersect_tube(t_object *tube, t_ray ray, t_intersect *j)
{
	t_root	roots;
	int		num_roots;

	roots.a = ray.direction.x * ray.direction.x +
				ray.direction.y * ray.direction.y;
	roots.b = 2 * (ray.direction.x * ray.origin.x +
				ray.direction.y * ray.origin.y);
	roots.c = ray.origin.x * ray.origin.x +
				ray.origin.y * ray.origin.y - RADIUS;
	num_roots = quadratic_roots(&roots);
	j->distance = INFINITY;
	j->is_inter = false;
	if (num_roots > 0)
		tube_body(ray, j, roots, num_roots);
	j->obj = tube;
	j->ray = ray;
	return (j->is_inter);
}
