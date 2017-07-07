/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_diff_spec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:41:47 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:41:50 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		shadow_inter(t_dif_tmp *tmp)
{
	if (tmp->cur->obj != NULL && tmp->cur->obj->solid == false)
		intersect_primitive(tmp->ray, &tmp->inter, tmp->cur);
	else if (tmp->cur->complex != NULL && tmp->cur->complex->solid == false)
		intersect_union(tmp->ray, &tmp->inter, tmp->cur);
	if (tmp->inter.is_inter && tmp->inter.obj->type != (int)MESH)
		intersect_param(tmp->inter.ray, &tmp->inter);
}

static bool		calculate_shadow_color(t_dif_tmp *tmp)
{
	if ((tmp->inter.obj->material.type != (int)GLASS ||
		check_texture_param(tmp->inter.obj->material,
		get_intersection_color(tmp->inter))) &&
		tmp->len < tmp->light_dist)
	{
		tmp->slide = false;
		tmp->flag = false;
		return (true);
	}
	else if (tmp->len < tmp->light_dist)
	{
		tmp->color = color_add(tmp->color, get_intersection_color(tmp->inter));
		if (tmp->inter.obj->material.slide)
			tmp->slide = tmp->inter.obj->material.slide;
		tmp->flag = true;
	}
	return (false);
}

static bool		find_shadow_inter(t_dif_tmp *tmp)
{
	tmp->color = color_zero();
	while (tmp->cur)
	{
		tmp->inter = intersection_zero();
		shadow_inter(tmp);
		if (tmp->inter.is_inter)
		{
			tmp->len = vector_length(
								vector_sub(tmp->inter.point, tmp->ray.origin));
			if (calculate_shadow_color(tmp))
				return (true);
		}
		tmp->cur = tmp->cur->next;
	}
	return (false);
}

static t_color	shadow_ray(t_scene *scene, t_light *light, t_color col,
													t_intersect inter_obj)
{
	t_dif_tmp	tmp;

	tmp.light_pos = (scene->shadow_samples == 1) ? light->position :
													get_position(light);
	tmp.light_dir = get_light_direction(light, tmp.light_pos, inter_obj.hit);
	tmp.ray.direction = vector_normalize(tmp.light_dir);
	tmp.ray.origin = inter_obj.hit;
	tmp.light_dist = vector_length(vector_sub(tmp.light_pos, tmp.ray.origin));
	tmp.flag = false;
	tmp.cur = scene->obj_list;
	if (find_shadow_inter(&tmp))
		return (color_zero());
	if (tmp.flag)
	{
		return (color_add(lighting(tmp.light_pos, light, col, inter_obj),
		color_mult(tmp.color, (tmp.slide) ? 1.0 : 0.2)));
	}
	return (lighting(tmp.light_pos, light, col, inter_obj));
}

t_color			get_diff_spec_color(t_color col, t_scene *scene,
													t_intersect inter_obj)
{
	t_color	diff_color;
	t_light	*l;
	int		j;

	l = scene->light;
	while (l)
	{
		diff_color = color_zero();
		j = -1;
		while (++j < scene->shadow_samples)
		{
			diff_color = color_add(diff_color,
						shadow_ray(scene, l, col, inter_obj));
		}
		col = color_add(col, color(diff_color.r / scene->shadow_samples,
									diff_color.g / scene->shadow_samples,
									diff_color.b / scene->shadow_samples));
		l = l->next;
	}
	return (col);
}
