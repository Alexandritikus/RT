/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:30:04 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 12:51:22 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	*choose_active_param(t_object *active)
{
	if (active->axis == 'x')
	{
		if (active->mode == ROTATE)
			return (&active->rot.x);
		else if (active->mode == TRANSLATE)
			return (&active->pos.x);
		return (&active->scale.x);
	}
	else if (active->axis == 'y')
	{
		if (active->mode == ROTATE)
			return (&active->rot.y);
		else if (active->mode == TRANSLATE)
			return (&active->pos.y);
		return (&active->scale.y);
	}
	else
	{
		if (active->mode == ROTATE)
			return (&active->rot.z);
		else if (active->mode == TRANSLATE)
			return (&active->pos.z);
		return (&active->scale.z);
	}
}

static double	*choose_active_param_u(t_union *active)
{
	if (active->axis == 'x')
	{
		if (active->mode == ROTATE)
			return (&active->rot.x);
		else if (active->mode == TRANSLATE)
			return (&active->pos.x);
		return (&active->scale.x);
	}
	else if (active->axis == 'y')
	{
		if (active->mode == ROTATE)
			return (&active->rot.y);
		else if (active->mode == TRANSLATE)
			return (&active->pos.y);
		return (&active->scale.y);
	}
	else
	{
		if (active->mode == ROTATE)
			return (&active->rot.z);
		else if (active->mode == TRANSLATE)
			return (&active->pos.z);
		return (&active->scale.z);
	}
}

static int		change_position_by_axis(int key, t_object *active)
{
	double	*curr_axis;

	if (active->complex)
		curr_axis = choose_active_param_u(active->complex);
	else
		curr_axis = choose_active_param(active);
	if (key == M_S_UP)
		*curr_axis += (active->mode == ROTATE) ? RAD_COEF * 10 : 0.1;
	else if (key == M_S_DOWN)
		*curr_axis -= (active->mode == ROTATE) ? RAD_COEF * 10 : 0.1;
	if (active->mode == SCALE)
		*curr_axis = MAX(0.1, *curr_axis);
	if (active->complex)
		change_union_matrix(active->complex);
	else
		change_object_matrix(active);
	return (2);
}

static t_object	*pic_active_object(t_env *env, int x, int y)
{
	double		xamnt;
	double		yamnt;
	t_ray		ray;
	t_intersect	inter;
	t_objs		*current;

	xamnt = -(2 * ((x + 0.5) / (double)env->sw_image) - 1)
													* ANGLE * env->aspect_ratio;
	yamnt = (1 - 2 * ((y + 0.5) / (double)env->sh)) * ANGLE;
	ray.origin = env->scene->camera->position;
	ray.direction = vector_normalize(matrix_to_vector(
						env->scene->camera->view, vector(xamnt, yamnt, -1), 0));
	inter = intersection_zero();
	current = env->scene->obj_list;
	while (current)
	{
		if (current->obj != NULL && current->obj->solid == false)
			intersect_primitive(ray, &inter, current);
		else if (current->complex != NULL && current->complex->solid == false)
			intersect_union(ray, &inter, current);
		current = current->next;
	}
	return (inter.is_inter ? inter.obj : NULL);
}

int				mouse_hook(int key, int x, int y, t_env *env)
{
	if (key == M_P_1)
	{
		if (env->mode == (int)MODE_TITLE)
			env->redraw = check_title(x, y, env);
		else if (env->mode == (int)MODE_PIC_LIST)
			env->redraw = check_pic_list(x, y, env);
		else
		{
			if ((env->redraw = home_button(x, y, env->sw_image)))
				env->mode = MODE_TITLE;
			else if ((env->redraw = scene_list_button(x, y, env->sw_image)))
				env->mode = MODE_PIC_LIST;
			else if (env->mode == (int)MODE_CREATE && env->scene->obj_list)
			{
				env->scene->active = pic_active_object(env, x, y);
				env->redraw = 3;
			}
		}
	}
	else if ((key == M_S_UP || key == M_S_DOWN) && env->scene->active)
		env->redraw = change_position_by_axis(key, env->scene->active);
	expose_hook(env);
	return (0);
}
