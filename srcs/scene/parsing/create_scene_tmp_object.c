/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene_tmp_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:01:03 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 12:12:16 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static t_union_tmp	*complex_data(void)
{
	t_union_tmp	*complex;

	complex = (t_union_tmp*)malloc(sizeof(t_union_tmp));
	complex->type = -1;
	complex->orientation.pos = vector_zero();
	complex->orientation.rot = vector_zero();
	complex->orientation.scale = vector(1.0, 1.0, 1.0);
	complex->array = NULL;
	return (complex);
}

static t_scene_tmp	*scene_data(void)
{
	t_scene_tmp	*data;

	data = (t_scene_tmp*)malloc(sizeof(t_scene_tmp));
	data->effects = true;
	data->ssaa = 1;
	data->max_reflections = 1;
	data->shadow_samples = 1;
	data->cam_position = vector_zero();
	data->cam_look_at = vector_zero();
	data->cam_rotation = vector_zero();
	data->sky_box_link = NULL;
	data->bg = NULL;
	data->bg_color = color_zero();
	return (data);
}

static t_obj_tmp	*obj_data(void)
{
	t_obj_tmp	*data;

	data = (t_obj_tmp*)malloc(sizeof(t_obj_tmp));
	data->solid = false;
	data->mesh_link = NULL;
	data->mesh = NULL;
	data->orientation.pos = vector_zero();
	data->orientation.rot = vector_zero();
	data->orientation.scale = vector(1.0, 1.0, 1.0);
	data->material = material_base();
	data->torus_in_radius = 0.5;
	return (data);
}

static t_light_tmp	*light_data(void)
{
	t_light_tmp	*data;

	data = (t_light_tmp*)malloc(sizeof(t_light_tmp));
	data->position = vector_zero();
	data->vertex = vector(0, 1, 0);
	data->color = color(1, 1, 1);
	data->intensity = 1.0;
	data->type = BASE_L;
	data->radius = 1.0;
	return (data);
}

t_scene_obj			*create_scene_object(int type)
{
	t_scene_obj	*object;

	object = (t_scene_obj*)malloc(sizeof(t_scene_obj));
	object->status = false;
	object->scene_data = NULL;
	object->light_data = NULL;
	object->obj_data = NULL;
	if (type == (int)SCENE)
		object->scene_data = scene_data();
	else if (type > (int)SCENE && type < (int)LIGHT)
		object->obj_data = obj_data();
	else if (type == (int)LIGHT)
		object->light_data = light_data();
	else if (type == (int)UNION)
		object->union_data = complex_data();
	return (object);
}
