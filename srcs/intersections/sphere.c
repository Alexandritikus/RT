/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:09:13 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:17:52 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void	intersect_sphere_param(t_ray ray, t_intersect *j)
{
	double theta;
	double phi;

	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	j->normal = j->point;
	theta = atan2(-j->normal.z, j->normal.x);
	phi = acos(-j->normal.y);
	j->u = (theta + M_PI) / (2 * M_PI);
	j->v = phi / M_PI;
	j->pu = vector(-sin(theta) * sin(phi), 0, -cos(theta) * sin(phi));
	j->pv = vector(cos(theta) * cos(phi), sin(phi), -sin(theta) * cos(phi));
}

bool	intersect_sphere(t_object *sphere, t_ray ray, t_intersect *j)
{
	t_root	roots;
	int		num_roots;
	double	min;

	roots.a = vector_dot(ray.direction, ray.direction);
	roots.b = vector_dot(vector_mult_d(ray.direction, 2), ray.origin);
	roots.c = vector_dot(ray.origin, ray.origin) - RADIUS;
	num_roots = quadratic_roots(&roots);
	if (num_roots > 0)
	{
		min = MIN(roots.roots_2[0], roots.roots_2[1]);
		if (num_roots == 1)
			j->distance = roots.roots_2[0];
		else if (min < 0)
			j->distance = MAX(roots.roots_2[0], roots.roots_2[1]);
		else
			j->distance = min;
		if (j->distance <= 0)
			return (false);
		j->is_inter = true;
		j->ray = ray;
		j->obj = sphere;
		return (true);
	}
	return (false);
}
