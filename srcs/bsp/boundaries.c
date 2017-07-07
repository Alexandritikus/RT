/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundaries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:32:55 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:32:57 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

t_boundaries	boundaries(void)
{
	t_boundaries	ret;

	ret.min = vector_zero();
	ret.max = vector_zero();
	return (ret);
}

double			split_value(t_boundaries bound, char axis)
{
	if (axis == 'x')
		return ((bound.min.x + bound.max.x) / 2);
	else if (axis == 'y')
		return ((bound.min.y + bound.max.y) / 2);
	else if (axis == 'z')
		return ((bound.min.z + bound.max.z) / 2);
	else
		return (0.0);
}

int				boundaries_intersect(t_boundaries bound, t_ray ray)
{
	t_vec	min;
	t_vec	max;
	double	tmin;
	double	tmax;

	min = vector((bound.min.x - ray.origin.x) * (1.0 / ray.direction.x),
				(bound.min.y - ray.origin.y) * (1.0 / ray.direction.y),
				(bound.min.z - ray.origin.z) * (1.0 / ray.direction.z));
	max = vector((bound.max.x - ray.origin.x) * (1.0 / ray.direction.x),
				(bound.max.y - ray.origin.y) * (1.0 / ray.direction.y),
				(bound.max.z - ray.origin.z) * (1.0 / ray.direction.z));
	tmin = MAX(MAX(MIN(min.x, max.x), MIN(min.y, max.y)), MIN(min.z, max.z));
	tmax = MIN(MIN(MAX(min.x, max.x), MAX(min.y, max.y)), MAX(min.z, max.z));
	if (tmax < 0)
		return (0);
	if (tmin > tmax)
		return (0);
	return (1);
}

void			mesh_update(t_object *obj)
{
	t_poly	*current;
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;

	current = obj->mesh->polygon;
	while (current)
	{
		current->bounds = boundaries();
		v1 = matrix_to_vector(obj->transform, current->triangle->v1, 1);
		v2 = matrix_to_vector(obj->transform, current->triangle->v2, 1);
		v3 = matrix_to_vector(obj->transform, current->triangle->v3, 1);
		current->bounds.max = vector(MAX(MAX(v1.x, v2.x), v3.x),
										MAX(MAX(v1.y, v2.y), v3.y),
										MAX(MAX(v1.z, v2.z), v3.z));
		current->bounds.min = vector(MIN(MIN(v1.x, v2.x), v3.x),
										MIN(MIN(v1.y, v2.y), v3.y),
										MIN(MIN(v1.z, v2.z), v3.z));
		current = current->next;
	}
}
