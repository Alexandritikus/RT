/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_reflect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:15:43 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 16:43:37 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	start_refl(t_scene *sc, t_intersect i_obj, int rr, t_refl_tmp *tmp)
{
	tmp->reflected = reflect(i_obj);
	if (!reflect_perturbed(i_obj, tmp->reflected, &tmp->refl_ray))
		tmp->refl_color = color_mult(
			intersect_object(sc, tmp->refl_ray, --rr), tmp->refl_percent);
}

static void	start_refr(t_scene *sc, t_intersect i_obj, int rr, t_refl_tmp *tmp)
{
	if (!refract(i_obj, &tmp->refr_ray))
		tmp->refr_color = color_mult(
			intersect_object(sc, tmp->refr_ray, --rr), tmp->refr_percent);
}

t_color		get_reflect_color(t_scene *scene, t_intersect inter_obj, int rr)
{
	t_refl_tmp	tmp;
	t_color		obj_col;

	obj_col = get_intersection_color(inter_obj);
	if (check_texture_param(inter_obj.obj->material, obj_col) ||
											inter_obj.obj->material.slide)
		return (color_zero());
	tmp.refl_percent = get_reflectivity(inter_obj.obj->material);
	tmp.refr_percent = 0;
	if ((tmp.refl_percent == NOT_REFLECTIVE &&
			get_refractive(inter_obj.obj->material) == NOT_REFRACTIVE) ||
			rr <= 0)
		return (color_zero());
	tmp.refl_color = color_zero();
	tmp.refr_color = color_zero();
	if (get_refractive(inter_obj.obj->material) != NOT_REFRACTIVE)
	{
		tmp.refl_percent = get_reflectance(inter_obj);
		tmp.refr_percent = 1 - tmp.refl_percent;
	}
	if (tmp.refl_percent > ACCURACY)
		start_refl(scene, inter_obj, rr, &tmp);
	if (tmp.refr_percent > ACCURACY)
		start_refr(scene, inter_obj, rr, &tmp);
	return (color_add(tmp.refl_color, tmp.refr_color));
}
