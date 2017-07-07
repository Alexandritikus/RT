/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:16:43 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:17:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	return_cord(t_vec p, int i)
{
	if (i == 0)
		return (p.x);
	else if (i == 1)
		return (p.y);
	else
		return (p.z);
}

bool	calculate_solid_intersect(t_ray ray, t_object *obj, t_intersect *inter)
{
	t_ray	tmp_ray;
	bool	intersects;

	intersects = false;
	*inter = intersection_zero();
	tmp_ray.origin = matrix_to_vector(obj->inverse, ray.origin, 1);
	tmp_ray.direction = matrix_to_vector(obj->inverse, ray.direction, 0);
	intersects = intersect_distance(obj, tmp_ray, inter);
	if (intersects)
	{
		intersect_param(inter->ray, inter);
		inter->point = matrix_to_vector(inter->obj->transform,
														inter->point, 1);
		inter->normal = matrix_to_vector(inter->obj->transpose,
														inter->normal, 0);
	}
	return (intersects);
}

void	choose_intersect(t_ray ray, t_intersect *inter, t_objs *current,
														t_solid_in_tmp s)
{
	if (fabs(ray.direction.x) > DBL_EPSILON)
		s.id = 0;
	else if (fabs(ray.direction.y) > DBL_EPSILON)
		s.id = 1;
	else
		s.id = 2;
	s.t = (return_cord(s.j.point, s.id) - return_cord(ray.origin, s.id)) /
											return_cord(ray.direction, s.id);
	s.new_ray.origin = vector_add(ray.origin, vector_mult_d(ray.direction,
												(s.t + 1000 * DBL_EPSILON)));
	s.new_ray.direction = ray.direction;
	s.inter_a = calculate_solid_intersect(s.new_ray,
								current->complex->obj_list->obj, &s.u);
	s.inter_b = calculate_solid_intersect(s.new_ray,
								current->complex->obj_list->next->obj, &s.v);
	if (!s.inter_b)
		*inter = s.j;
	else if (s.inter_a && dist_to_dot(s.v.point, ray.origin) <
								dist_to_dot(s.u.point, ray.origin))
	{
		*inter = s.v;
		inter->is_normal = true;
	}
}

void	intersect_solid_in(t_ray ray, t_intersect *inter, t_objs *current)
{
	t_solid_in_tmp	solid;

	ray.origin = matrix_to_vector(current->complex->inverse,
														ray.origin, 1);
	ray.direction = matrix_to_vector(current->complex->inverse,
														ray.direction, 0);
	solid.inter_a = calculate_solid_intersect(ray,
							current->complex->obj_list->obj, &solid.j);
	solid.inter_b = calculate_solid_intersect(ray,
							current->complex->obj_list->next->obj, &solid.k);
	if (solid.inter_a)
	{
		if (solid.inter_b && dist_to_dot(solid.k.point, ray.origin) <
										dist_to_dot(solid.j.point, ray.origin))
			choose_intersect(ray, inter, current, solid);
		else
			*inter = solid.j;
	}
}
