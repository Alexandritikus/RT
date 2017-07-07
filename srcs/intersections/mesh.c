/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 20:16:16 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:24:50 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	ini_for_mesh(t_poly *cur, t_ray ray, t_mesh_temp *tmp)
{
	tmp->a = cur->triangle->v1;
	tmp->b = cur->triangle->v2;
	tmp->c = cur->triangle->v3;
	tmp->e1 = vector_sub(tmp->b, tmp->a);
	tmp->e2 = vector_sub(tmp->c, tmp->a);
	tmp->pp = vector_cross(ray.direction, tmp->e2);
	tmp->det = vector_dot(tmp->pp, tmp->e1);
}

static void	final_for_mesh(t_object *mesh, t_intersect *j, t_poly *cur,
														t_mesh_temp *tmp)
{
	tmp->u = tmp->p_e1 * tmp->u;
	tmp->v = tmp->p_e1 * tmp->v;
	if (mesh->mesh->face_type == (int)V_NORM)
		j->normal = vector_add(vector_add(
			vector_mult_d(cur->normal->v1, 1 - tmp->u - tmp->v),
			vector_mult_d(cur->normal->v2, tmp->u)),
			vector_mult_d(cur->normal->v3, tmp->v));
	else
		j->normal = vector_cross(vector_sub(tmp->b, tmp->a),
												vector_sub(tmp->c, tmp->a));
	tmp->intersected = true;
	tmp->prev_t = tmp->t;
	j->obj = mesh;
	j->is_inter = true;
	j->distance = tmp->t;
	j->u = tmp->u;
	j->v = tmp->v;
}

static bool	check_intersect(t_ray ray, t_mesh_temp *tmp)
{
	if (fabs(tmp->det) < DBL_EPSILON)
		return (false);
	tmp->tt = vector_sub(ray.origin, tmp->a);
	tmp->u = vector_dot(tmp->pp, tmp->tt);
	if (tmp->u < 0 || tmp->u > tmp->det)
		return (false);
	tmp->qq = vector_cross(tmp->tt, tmp->e1);
	tmp->v = vector_dot(tmp->qq, ray.direction);
	if (tmp->v < 0 || tmp->v > (tmp->det - tmp->u))
		return (false);
	tmp->p_e1 = 1.0 / vector_dot(tmp->pp, tmp->e1);
	tmp->t = tmp->p_e1 * vector_dot(tmp->qq, tmp->e2);
	if (tmp->t < 0 || tmp->t > tmp->prev_t)
		return (false);
	return (true);
}

bool		intersect_mesh(t_object *mesh, t_ray ray, t_intersect *j,
														t_poly *poly_list)
{
	t_mesh_temp	tmp;
	t_poly		*cur;

	cur = poly_list;
	tmp.intersected = false;
	tmp.prev_t = INFINITY;
	while (cur)
	{
		ini_for_mesh(cur, ray, &tmp);
		if (!check_intersect(ray, &tmp))
		{
			cur = cur->next;
			continue;
		}
		final_for_mesh(mesh, j, cur, &tmp);
		j->point = vector_add(ray.origin, vector_mult_d(ray.direction, tmp.t));
		j->ray = ray;
		cur = cur->next;
	}
	return (tmp.intersected);
}
