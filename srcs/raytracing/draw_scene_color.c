/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:19:07 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/10 11:41:05 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	texture_color(t_intersect inter)
{
	double	di;
	double	dj;
	int		i1;
	int		j1;

	di = (1.0 - inter.u) * (double)(inter.obj->material.texture->width - 1);
	dj = (1.0 - inter.v) * (double)(inter.obj->material.texture->height - 1);
	i1 = ((di + 1) >= inter.obj->material.texture->width) ? 0 : di + 1;
	j1 = ((dj + 1) >= inter.obj->material.texture->height) ? 0 : dj + 1;
	return (color_from_pixel(inter.obj->material.texture, i1, j1));
}

t_color			get_intersection_color(t_intersect inter)
{
	if (inter.obj->material.texture != NULL)
		return (texture_color(inter));
	else if (inter.obj->material.type == (int)AIR ||
		inter.obj->material.type == (int)FLATCOLOR ||
		inter.obj->material.type == (int)GLASS ||
		inter.obj->material.type == (int)SHINYCOLOR)
		return (get_afgs_color(inter.obj->material, inter.point));
	else if (inter.obj->material.type == (int)CHECKBOARD)
		return (get_checkerboard_color(inter.obj->material, inter.point));
	else if (inter.obj->material.type == (int)MARBLE)
		return (get_marble_color(inter.obj->material, inter.point));
	else if (inter.obj->material.type == (int)TURBULENCE)
		return (get_turbulence_color(inter.obj->material, inter.point));
	else if (inter.obj->material.type == (int)WOOD)
		return (get_wood_color(inter.obj->material, inter.point));
	else if (inter.obj->material.type == (int)CRISSCROSS)
		return (get_crisscross_color(inter.obj->material, inter.point));
	else
		return (color_zero());
}

t_color			color_estimate(t_scene *scene, t_intersect inter_obj, int rr)
{
	t_color	color;
	t_color	ambient_color;
	t_color	diff_spec_color;
	t_color	reflect;

	color = get_intersection_color(inter_obj);
	ambient_color = color_zero();
	reflect = color_zero();
	if (scene->effects)
	{
		ambient_color = color_mult(color, scene->ambient_light);
		diff_spec_color = get_diff_spec_color(ambient_color, scene, inter_obj);
		reflect = get_reflect_color(scene, inter_obj, rr);
	}
	else
		diff_spec_color = color;
	return (color_add(color_add(ambient_color, diff_spec_color), reflect));
}
