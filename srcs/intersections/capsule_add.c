/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:10:32 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:09:07 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

t_sphere		cyl_sphere(t_vec pos, double r)
{
	t_sphere	sphere;

	sphere.pos = pos;
	sphere.r = r;
	return (sphere);
}

bool			intersect_cyl_sphere(t_sphere sphere, t_ray ray, t_intersect *j)
{
	t_root		roots;
	int			num_roots;
	double		min;

	roots.a = vector_dot(ray.direction, ray.direction);
	roots.b = vector_dot(vector_mult_d(ray.direction, 2),
							vector_sub(ray.origin, sphere.pos));
	roots.c = vector_dot(vector_sub(ray.origin, sphere.pos),
				vector_sub(ray.origin, sphere.pos)) - sphere.r * sphere.r;
	num_roots = quadratic_roots(&roots);
	if (num_roots == 0)
		return (false);
	min = MIN(roots.roots_2[0], roots.roots_2[1]);
	if (num_roots == 1)
		j->distance = roots.roots_2[0];
	else if (min < 0)
		j->distance = MAX(roots.roots_2[0], roots.roots_2[1]);
	else
		j->distance = min;
	if (j->distance <= 0)
		return (false);
	j->point = vector_add(ray.origin,
			vector_mult_d(ray.direction, j->distance));
	j->is_inter = true;
	return (true);
}
