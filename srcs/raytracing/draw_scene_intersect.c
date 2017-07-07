/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 11:54:08 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/05 13:46:28 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

bool		intersect_distance(t_object *object, t_ray ray, t_intersect *inter)
{
	if (object->type == (int)SPHERE)
		return (intersect_sphere(object, ray, inter));
	if (object->type == (int)CYLINDER)
		return (intersect_cylinder(object, ray, inter));
	else if (object->type == (int)CONE)
		return (intersect_cone(object, ray, inter));
	else if (object->type == (int)PLANE)
		return (intersect_plane(object, ray, inter));
	else if (object->type == (int)DISC)
		return (intersect_disc(object, ray, inter));
	else if (object->type == (int)TRIANGLE)
		return (intersect_triangle(object, ray, inter));
	else if (object->type == (int)TORUS)
		return (intersect_torus(object, ray, inter));
	else if (object->type == (int)CUBE)
		return (intersect_cube(object, ray, inter));
	else if (object->type == (int)TUBE)
		return (intersect_tube(object, ray, inter));
	else if (object->type == (int)CAPSULE)
		return (intersect_capsule(object, ray, inter));
	else if (object->type == (int)PARABOLOID)
		return (intersect_paraboloid(object, ray, inter));
	else if (object->type == (int)MOEBIUS)
		return (intersect_moebius(object, ray, inter));
	return (false);
}

void		intersect_param(t_ray ray, t_intersect *inter)
{
	if (inter->obj->type == (int)SPHERE)
		intersect_sphere_param(ray, inter);
	else if (inter->obj->type == (int)CYLINDER)
		intersect_cylinder_param(ray, inter);
	else if (inter->obj->type == (int)CAPSULE)
		intersect_capsule_param(ray, inter);
	else if (inter->obj->type == (int)TUBE)
		intersect_tube_param(ray, inter);
	else if (inter->obj->type == (int)TORUS)
		intersect_torus_param(ray, inter);
	else if (inter->obj->type == (int)PLANE)
		intersect_plane_param(inter);
	else if (inter->obj->type == (int)DISC)
		intersect_disc_param(ray, inter);
	else if (inter->obj->type == (int)CUBE)
		intersect_cube_param(ray, inter);
	else if (inter->obj->type == (int)MOEBIUS)
		intersect_moebius_param(ray, inter);
}

t_intersect	intersection_zero(void)
{
	t_intersect	inter;

	inter.is_inter = false;
	inter.is_normal = false;
	inter.distance = INFINITY;
	inter.point = vector_zero();
	inter.normal = vector_zero();
	inter.u = 0.0;
	inter.v = 0.0;
	inter.n = vector_zero();
	inter.hit = vector_zero();
	inter.pu = vector_zero();
	inter.pv = vector_zero();
	inter.obj = NULL;
	return (inter);
}

t_color		intersect_object(t_scene *scene, t_ray ray, int rr)
{
	t_intersect	inter;
	t_objs		*current;

	inter = intersection_zero();
	current = scene->obj_list;
	while (current)
	{
		if (current->obj != NULL && current->obj->solid == false)
			intersect_primitive(ray, &inter, current);
		else if (current->complex != NULL && current->complex->solid == false)
			intersect_union(ray, &inter, current);
		current = current->next;
	}
	if (inter.is_inter && inter.obj->type != (int)MESH)
		calculate_param(ray, &inter);
	return (inter.is_inter ? color_estimate(scene, inter, rr) :
												bg_color(scene, ray));
}
