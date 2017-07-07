/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_diff_spec_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:41:57 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:42:00 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_attenuation(t_light *light, double r)
{
	return (1.0 / (light->falloff.x +
				light->falloff.y * r +
				light->falloff.z * (r * r)));
}

t_color			lighting(t_vec light_pos, t_light *light, t_color col,
															t_intersect i_obj)
{
	t_dif_tmp	tmp;
	t_color		light_col;
	t_color		specular;
	t_color		diffuse;

	specular = color_zero();
	light_col = get_light_color(light, light_pos, i_obj.hit);
	tmp.surf_light = vector_sub(light_pos, i_obj.point);
	tmp.distance_to_light = vector_length(tmp.surf_light);
	tmp.surf_light = vector_normalize(tmp.surf_light);
	tmp.dif_br = MAX(0.0, vector_dot(i_obj.n, tmp.surf_light));
	diffuse = color_mult(color_mult_color(color_mult(col, tmp.dif_br),
												light_col), light->intensity);
	tmp.surf_eye = vector_normalize(vector_sub(i_obj.ray.origin, i_obj.point));
	tmp.halfway = vector_normalize(vector_add(tmp.surf_light, tmp.surf_eye));
	if (i_obj.obj->material.shininess != NOT_SHINY)
	{
		tmp.spec_br = (tmp.dif_br > 0) ? pow(MAX(0.0, vector_dot(i_obj.n,
					tmp.halfway)), i_obj.obj->material.shininess) : 0.0;
		specular = color_mult(color_mult_color(color_mult(light_col,
					tmp.spec_br), light_col), light->intensity);
	}
	return (color_mult(color_add(diffuse, specular),
						get_attenuation(light, tmp.distance_to_light)));
}
