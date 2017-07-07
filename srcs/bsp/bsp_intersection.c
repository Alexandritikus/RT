/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:45:31 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/10 07:35:43 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

t_intersect	get_closest_intersect(t_bsp *bsp, t_ray ray, t_object *mesh)
{
	t_intersect	left_inter;
	t_intersect	right_inter;

	if (!boundaries_intersect(bsp->bounds, ray))
		return (intersection_zero());
	if (bsp->left != NULL && bsp->right != NULL)
	{
		left_inter = get_closest_intersect(bsp->left, ray, mesh);
		right_inter = get_closest_intersect(bsp->right, ray, mesh);
		return (left_inter.distance < right_inter.distance ?
										left_inter : right_inter);
	}
	else
		return (get_branch_intersect(bsp, ray, mesh));
}

t_intersect	get_branch_intersect(t_bsp *bsp, t_ray ray, t_object *mesh)
{
	t_intersect	inter;
	t_ray		tmp_ray;

	inter = intersection_zero();
	tmp_ray = ray;
	tmp_ray.origin = matrix_to_vector(mesh->inverse, ray.origin, 1);
	tmp_ray.direction = matrix_to_vector(mesh->inverse, ray.direction, 0);
	if (intersect_mesh(mesh, tmp_ray, &inter, bsp->poly_list))
	{
		inter.ray = ray;
		inter.point = matrix_to_vector(mesh->transform, inter.point, 1);
		inter.normal = matrix_to_vector(mesh->transpose, inter.normal, 0);
		inter.n = vector_normalize(inter.normal);
		inter.hit = vector_add(inter.point, vector_mult_d(inter.n, 1e-9));
	}
	return (inter);
}
