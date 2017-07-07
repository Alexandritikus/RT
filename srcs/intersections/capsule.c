/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:10:23 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:11:03 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void		cylinder_body(t_ray ray, t_intersect *j, t_root roots,
													size_t num_roots)
{
	double		t2;
	double		z1;
	double		z2;

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
		{
			j->is_inter = true;
			j->type = 0;
		}
	}
}

static void		cylinder_spheres(t_ray ray, t_intersect *j)
{
	t_intersect	iends;
	double		t;

	if (intersect_cyl_sphere(cyl_sphere(
					vector(0.0, 0.0, -(HEIGHT / 2.0)), RADIUS), ray, &iends))
	{
		t = (iends.point.x - ray.origin.x) / ray.direction.x;
		if (t < j->distance)
		{
			j->distance = t;
			j->is_inter = true;
			j->type = 1;
		}
	}
	if (intersect_cyl_sphere(cyl_sphere(
					vector(0.0, 0.0, HEIGHT / 2.0), RADIUS), ray, &iends))
	{
		t = (iends.point.x - ray.origin.x) / ray.direction.x;
		if (t < j->distance)
		{
			j->distance = t;
			j->is_inter = true;
			j->type = 2;
		}
	}
}

void			intersect_capsule_param(t_ray ray, t_intersect *j)
{
	double		theta;
	double		phi;

	j->point = vector_add(ray.origin,
					vector_mult_d(ray.direction, j->distance));
	if (j->type == 0)
	{
		j->normal = j->point;
		j->u = acos(vector_dot(vector(j->normal.x, j->normal.y, 0.0),
								vector(1.0, 0.0, 0.0))) / M_PI;
		j->v = j->normal.z + 0.5;
		j->normal.z = 0.0;
	}
	else
	{
		if (j->type == 1)
			j->normal = vector_sub(j->point, vector(0.0, 0.0, -HEIGHT / 2.0));
		else
			j->normal = vector_sub(j->point, vector(0.0, 0.0, HEIGHT / 2.0));
		theta = atan2(-j->normal.z, j->normal.x);
		phi = acos(-j->normal.y);
		j->u = (theta + M_PI) / (2 * M_PI);
		j->v = phi / M_PI;
	}
}

bool			intersect_capsule(t_object *capsule, t_ray ray, t_intersect *j)
{
	t_root		roots;
	int			num_roots;

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
		cylinder_body(ray, j, roots, num_roots);
	cylinder_spheres(ray, j);
	j->obj = capsule;
	j->ray = ray;
	return (j->is_inter);
}
