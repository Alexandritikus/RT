/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:17:36 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:17:41 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	intersect_solid_out(t_ray ray, t_intersect *inter, t_objs *obj)
{
	bool		intersects_a;
	bool		intersects_b;
	t_ray		n_ray;
	t_intersect	x;
	t_intersect	y;

	x = intersection_zero();
	y = intersection_zero();
	ray.origin = matrix_to_vector(obj->complex->inverse, ray.origin, 1);
	ray.direction = matrix_to_vector(obj->complex->inverse, ray.direction, 0);
	n_ray.origin = matrix_to_vector(obj->complex->obj_list->obj->inverse,
													ray.origin, 1);
	n_ray.direction = matrix_to_vector(obj->complex->obj_list->obj->inverse,
													ray.direction, 0);
	intersects_a = intersect_distance(obj->complex->obj_list->obj, n_ray, &x);
	n_ray.origin = matrix_to_vector(obj->complex->obj_list->next->obj->inverse,
													ray.origin, 1);
	n_ray.direction = matrix_to_vector(
									obj->complex->obj_list->next->obj->inverse,
													ray.direction, 0);
	intersects_b = intersect_distance(obj->complex->obj_list->next->obj,
													n_ray, &y);
	if (intersects_a && intersects_b)
		*inter = (y.distance > x.distance) ? y : x;
}
