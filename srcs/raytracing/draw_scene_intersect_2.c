/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_intersect_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 11:28:04 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/10 11:30:19 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

void	intersect_primitive(t_ray ray, t_intersect *inter, t_objs *current)
{
	t_intersect	tmp_inter;
	t_ray		tmp_ray;

	tmp_inter = intersection_zero();
	if (current->obj->type == (int)MESH)
	{
		tmp_inter = get_closest_intersect(current->obj->mesh->bsp, ray,
														current->obj);
		if (tmp_inter.distance < inter->distance)
			*inter = tmp_inter;
	}
	else
	{
		tmp_ray.origin = matrix_to_vector(current->obj->inverse, ray.origin, 1);
		tmp_ray.direction = matrix_to_vector(current->obj->inverse,
														ray.direction, 0);
		if (intersect_distance(current->obj, tmp_ray, &tmp_inter) &&
										tmp_inter.distance < inter->distance)
			*inter = tmp_inter;
	}
}

void	intersect_union(t_ray ray, t_intersect *inter, t_objs *current)
{
	if (current->complex->type == (int)COMPOSE)
		intersect_compose(ray, inter, current);
	else if (current->complex->type == (int)SOLID_OUT)
		intersect_solid_out(ray, inter, current);
	else if (current->complex->type == (int)SOLID_IN)
		intersect_solid_in(ray, inter, current);
}

void	calculate_param(t_ray ray, t_intersect *inter)
{
	intersect_param(inter->ray, inter);
	inter->ray = ray;
	inter->point = matrix_to_vector(inter->obj->transform, inter->point, 1);
	inter->normal = matrix_to_vector(inter->obj->transpose, inter->normal, 0);
	if (inter->obj->complex)
	{
		inter->point = matrix_to_vector(
				inter->obj->complex->transform, inter->point, 1);
		inter->normal = matrix_to_vector(
				inter->obj->complex->transform, inter->normal, 0);
	}
	if (inter->is_normal)
		inter->normal = vector_mult_d(inter->normal, -1);
	inter->n = vector_normalize(inter->normal);
	if (inter->obj->material.bump_map != NULL)
		inter->n = bump(*inter);
	else if (inter->obj->material.is_normal)
		inter->n = mater_modify_normal(inter->obj->material, inter->n,
																inter->point);
	inter->hit = vector_add(inter->point, vector_mult_d(inter->n, ACCURACY));
}
