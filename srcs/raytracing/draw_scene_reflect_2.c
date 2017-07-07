/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_reflect_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:41:36 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:41:39 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		reflect_perturbed(t_intersect inter_obj, t_ray refl,
														t_ray *refl_ray)
{
	t_vec	na;
	t_vec	u;

	na = vector_mult_d(refl.direction, -1);
	if (na.z > na.x && na.z > na.y)
		u = vector(-na.y, na.x, 0.0);
	else if (na.y > na.x)
		u = vector(-na.z, 0.0, na.x);
	else
		u = vector(0.0, -na.z, na.y);
	u = vector_normalize(u);
	refl_ray->origin = refl.origin;
	refl_ray->direction = vector_normalize(refl.direction);
	return (vector_dot(inter_obj.n, refl.direction) < 0);
}

t_ray		reflect(t_intersect inter_obj)
{
	t_ray refl_ray;

	refl_ray.origin = inter_obj.hit;
	refl_ray.direction = vector_sub(inter_obj.ray.direction,
				vector_mult_d(inter_obj.n, 2 *
				vector_dot(inter_obj.ray.direction, inter_obj.n)));
	return (refl_ray);
}

static void	ini_refract(t_intersect inter_obj, t_refr_tmp *refr)
{
	if (refr->ci > 0)
	{
		refr->n1 = get_refractive(inter_obj.obj->material);
		refr->n2 = 1.0;
		refr->normal = vector_mult_d(refr->normal, -1);
	}
	else
	{
		refr->n1 = 1.0;
		refr->n2 = get_refractive(inter_obj.obj->material);
		refr->ci = -refr->ci;
	}
}

bool		refract(t_intersect inter_obj, t_ray *refracted)
{
	t_refr_tmp	refr;

	refr.normal = inter_obj.n;
	refr.ci = vector_dot(inter_obj.ray.direction, refr.normal);
	ini_refract(inter_obj, &refr);
	refr.nr = refr.n1 / refr.n2;
	refr.ct = 1.0 - (refr.nr * refr.nr) * (1.0 - (refr.ci * refr.ci));
	if (refr.ct >= 0)
	{
		refr.ct = sqrt(refr.ct);
		refracted->origin = vector_sub(inter_obj.point,
			vector_mult_d(refr.normal, (1e-9)));
		refracted->direction = vector_normalize(vector_add(
			vector_mult_d(inter_obj.ray.direction, refr.nr),
			vector_mult_d(refr.normal, (refr.nr * refr.ci - refr.ct))));
	}
	return (refr.ct < 0);
}

double		get_reflectance(t_intersect inter_obj)
{
	t_refr_tmp	r;

	r.normal = inter_obj.n;
	r.ci = vector_dot(inter_obj.ray.direction, r.normal);
	if (r.ci > 0)
	{
		r.n1 = get_refractive(inter_obj.obj->material);
		r.n2 = 1.0;
		r.normal = vector_mult_d(r.normal, -1);
	}
	else
	{
		r.n1 = 1.0;
		r.n2 = get_refractive(inter_obj.obj->material);
		r.ci = -r.ci;
	}
	r.nr = r.n1 / r.n2;
	r.ct = 1.0 - (r.nr * r.nr) * (1.0 - (r.ci * r.ci));
	if (r.ct < 0)
		return (1);
	r.ct = sqrt(r.ct);
	r.a = (r.n1 * r.ci - r.n2 * r.ct) / (r.n1 * r.ci + r.n2 * r.ct);
	r.b = (r.n2 * r.ci - r.n1 * r.ct) / (r.n2 * r.ci + r.n1 * r.ct);
	return ((r.a * r.a) + (r.b * r.b)) * 0.5;
}
