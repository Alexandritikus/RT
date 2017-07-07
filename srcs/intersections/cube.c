/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:08:19 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 11:50:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void			intersect_cube_param(t_ray ray, t_intersect *j)
{
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	if (fabs(j->normal.z) > fabs(j->normal.x) &&
		fabs(j->normal.z) > fabs(j->normal.y))
	{
		j->u = j->point.x / SIZE;
		j->v = j->point.y / SIZE;
	}
	else if (fabs(j->normal.y) > fabs(j->normal.x))
	{
		j->u = j->point.x / SIZE;
		j->v = j->point.z / SIZE;
	}
	else
	{
		j->u = j->point.y / SIZE;
		j->v = j->point.z / SIZE;
	}
	if (j->normal.z <= j->normal.x && j->normal.z <= j->normal.y)
		j->pu = vector(-j->normal.y, j->normal.x, 0.0);
	else if (j->normal.y <= j->normal.x)
		j->pu = vector(-j->normal.z, 0, j->normal.x);
	else
		j->pu = vector(0, -j->normal.z, j->normal.y);
	j->pv = vector_cross(j->normal, j->pu);
}

static void		ini_distance(t_cube_tmp tmp, t_intersect *j)
{
	j->distance = tmp.tmin;
	j->normal = tmp.nmin;
	if (tmp.tmin < 0)
	{
		j->distance = tmp.tmax;
		j->normal = tmp.nmax;
	}
}

bool			intersect_cube(t_object *cube, t_ray ray, t_intersect *j)
{
	t_cube_tmp	tmp;

	tmp.r_dir = vector(1.0 / ray.direction.x,
						1.0 / ray.direction.y,
						1.0 / ray.direction.z);
	tmp.bmin = vector_zero();
	tmp.bmax = vector(SIZE, SIZE, SIZE);
	x_plane(ray, &tmp);
	y_plane(ray, &tmp);
	if (tmp.tmax < tmp.tymin || tmp.tymax < tmp.tmin)
		return (false);
	first_swap(&tmp);
	z_plane(ray, &tmp);
	if (tmp.tmax < tmp.tzmin || tmp.tzmax < tmp.tmin)
		return (false);
	second_swap(&tmp);
	ini_distance(tmp, j);
	if (j->distance < 0)
		return (false);
	j->is_inter = true;
	j->obj = cube;
	j->ray = ray;
	return (true);
}
