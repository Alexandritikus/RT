/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:09:00 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/06 14:07:55 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void	update_scene_param(t_scene **scene, t_scene_tmp *data)
{
	(*scene)->effects = data->effects;
	(*scene)->ssaa = data->ssaa;
	(*scene)->antialias = (data->ssaa > 1 ? true : false);
	(*scene)->max_reflections = data->max_reflections;
	(*scene)->shadow_samples = data->shadow_samples;
	(*scene)->camera = camera(data->cam_position,
							data->cam_look_at,
							data->cam_rotation);
	(*scene)->bg = data->bg;
	(*scene)->bg_color = data->bg_color;
}

static void	update_light(t_light **light, t_light_tmp *data)
{
	t_vec	perp;

	while (*light)
		light = &(*light)->next;
	*light = (t_light*)malloc(sizeof(t_light));
	(*light)->position = data->position;
	(*light)->color = data->color;
	(*light)->intensity = data->intensity;
	(*light)->radius = data->radius;
	(*light)->falloff = vector(1, 0, 0);
	(*light)->normal = vector_normalize(vector_negative(data->position));
	if ((*light)->normal.z <= (*light)->normal.x &&
		(*light)->normal.z <= (*light)->normal.y)
		perp = vector(-(*light)->normal.y, (*light)->normal.x, 0.0);
	else if ((*light)->normal.y <= (*light)->normal.x)
		perp = vector(-(*light)->normal.z, 0.0, (*light)->normal.x);
	else
		perp = vector(0.0, -(*light)->normal.z, (*light)->normal.y);
	(*light)->perp = vector_normalize(perp);
	(*light)->type = data->type;
	(*light)->vertex = vector_normalize(data->vertex);
	(*light)->next = NULL;
}

static void	update_obj_list(t_objs **obj_list, t_obj_tmp *data, int type)
{
	if (type != (int)MESH || (type == (int)MESH && data->mesh))
	{
		while (*obj_list)
			obj_list = &(*obj_list)->next;
		*obj_list = (t_objs*)malloc(sizeof(t_objs));
		(*obj_list)->obj = object_3d(type, data->orientation,
									fix_material(data->material), data->solid);
		(*obj_list)->complex = NULL;
		if (type == (int)MESH)
		{
			(*obj_list)->obj->mesh = data->mesh;
			mesh_update((*obj_list)->obj);
			(*obj_list)->obj->mesh->bsp = bsp_tree(0, 'x',
											(*obj_list)->obj->mesh->polygon);
		}
		(*obj_list)->next = NULL;
	}
}

static void	update_union(t_objs **obj_list, t_union_tmp *data)
{
	t_objs	*obj;

	if (data->type != -1)
	{
		obj = (t_objs*)malloc(sizeof(t_objs));
		(obj)->obj = NULL;
		if ((obj->complex = union_3d(data, obj_list)) == NULL)
		{
			free(obj);
			obj = NULL;
		}
		else
		{
			obj->next = NULL;
			while (*obj_list)
				obj_list = &(*obj_list)->next;
			(*obj_list) = obj;
		}
	}
	ft_tabdel(&data->array);
}

void		update_scene(t_scene_obj **s_obj, t_scene **s, int *t)
{
	if (*t == (int)SCENE)
	{
		update_scene_param(s, (*s_obj)->scene_data);
		free((*s_obj)->scene_data);
	}
	else if (*t > (int)SCENE && *t < (int)LIGHT)
	{
		update_obj_list(&(*s)->obj_list, (*s_obj)->obj_data, *t);
		free((*s_obj)->obj_data);
	}
	else if (*t == (int)LIGHT)
	{
		update_light(&(*s)->light, (*s_obj)->light_data);
		free((*s_obj)->light_data);
	}
	else if (*t == (int)UNION)
	{
		update_union(&(*s)->obj_list, (*s_obj)->union_data);
		free((*s_obj)->union_data);
	}
	*t = -1;
	free(*s_obj);
	*s_obj = NULL;
}
