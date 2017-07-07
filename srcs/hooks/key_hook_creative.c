/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_creative.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:28:34 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 12:10:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object	*new_object(int type)
{
	t_orient	orient;
	t_material	material;
	t_object	*new_obj;

	orient.pos = vector_zero();
	orient.rot = vector_zero();
	orient.scale = vector(1.0, 1.0, 1.0);
	material = material_base();
	new_obj = object_3d(type, orient, material, false);
	return (new_obj);
}

static int		create_new_object(t_env **env, int key)
{
	t_objs	*obj;

	if (key == KEY_O || key == KEY_I || key == KEY_P || key == KEY_C)
	{
		obj = (t_objs*)malloc(sizeof(t_objs));
		obj->complex = NULL;
		if (key == KEY_O)
			obj->obj = new_object(SPHERE);
		else if (key == KEY_I)
			obj->obj = new_object(CYLINDER);
		else if (key == KEY_P)
			obj->obj = new_object(PLANE);
		else if (key == KEY_C)
			obj->obj = new_object(CONE);
		obj->next = (*env)->scene->obj_list;
		(*env)->scene->obj_list = obj;
		(*env)->redraw = 2;
		return (1);
	}
	else
		return (0);
}

static void		change_material_type(t_object *active, int key, int *redraw)
{
	if (key == KEY_OPEN_BRACKET)
	{
		if (active->material.type > 2)
		{
			active->material.type -= 1;
			if (active->material.type == 4)
				active->material.type -= 1;
		}
		else
			*redraw = 3;
	}
	if (key == KEY_CLOSE_BRACKET)
	{
		if (active->material.type < 8)
		{
			active->material.type += 1;
			if (active->material.type == 1 || active->material.type == 4)
				active->material.type += 1;
		}
		else
			*redraw = 3;
	}
	active->material = fix_material(active->material);
}

static int		material_manipulate(t_env *env, int key)
{
	if (key == KEY_0 && env->scene->active->material.scale < 5)
		env->scene->active->material.scale += 0.1;
	else if (key == KEY_9 && env->scene->active->material.scale > ACCURACY)
		env->scene->active->material.scale -= 0.1;
	else if (key == KEY_OPEN_BRACKET || key == KEY_CLOSE_BRACKET)
		change_material_type(env->scene->active, key, &env->redraw);
	else
		return (0);
	env->redraw = (env->redraw == 3 ? 3 : 2);
	return (1);
}

int				key_creative(t_env *env, int key)
{
	if (create_new_object(&env, key))
		return (1);
	else if (env->scene->active == NULL)
		return (0);
	if (key == KEY_DEL)
	{
		env->scene->active->complex ? (env->scene->active->complex->solid = 1)
											: (env->scene->active->solid = 1);
		env->scene->active = NULL;
		env->redraw = 2;
	}
	else if (key == KEY_LESS_THAN)
		axis_modify(env->scene->active, 0);
	else if (key == KEY_GREATER_THAN)
		axis_modify(env->scene->active, 1);
	else if (key == KEY_N)
		mode_modify(env->scene->active, 0);
	else if (key == KEY_M)
		mode_modify(env->scene->active, 1);
	else if (material_manipulate(env, key) ||
						color_manipulate(env->scene->active, key, &env->redraw))
		return (1);
	else
		return (0);
	return (1);
}
