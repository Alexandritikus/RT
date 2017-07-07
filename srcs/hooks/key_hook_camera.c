/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:38:39 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 11:39:37 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	camera_move(t_scene *scene, int key)
{
	t_vec	xyz;

	xyz = vector_zero();
	if (key == KEY_A)
		xyz.x = -0.3 * scene->lvl;
	else if (key == KEY_D)
		xyz.x = 0.3 * scene->lvl;
	else if (key == KEY_W)
		xyz.z = 0.3 * scene->lvl;
	else if (key == KEY_S)
		xyz.z = -0.3 * scene->lvl;
	else if (key == KEY_MINUS)
		xyz.y = -0.3 * scene->lvl;
	else if (key == KEY_EQUAL)
		xyz.y = 0.3 * scene->lvl;
	else
		return (0);
	scene->camera->position = vector_add(scene->camera->position, xyz);
	scene->camera->look_at = vector_add(scene->camera->look_at, xyz);
	return (1);
}

static int	camera_rotate(t_scene *scene, int key)
{
	double	x;
	double	y;
	t_vec	vec;

	x = 0.0;
	y = 0.0;
	if (key == KEY_LEFT)
		y = 0.01 * scene->lvl;
	else if (key == KEY_RIGHT)
		y = -0.01 * scene->lvl;
	else if (key == KEY_UP)
		x = -0.01 * scene->lvl;
	else if (key == KEY_DOWN)
		x = 0.01 * scene->lvl;
	else
		return (0);
	vec = scene->camera->rotation;
	scene->camera->rotation = vector(vec.x + x, vec.y + y, vec.z);
	calculate_view(scene->camera);
	return (1);
}

int			key_camera(t_scene *scene, int key, int *redraw)
{
	if (camera_move(scene, key))
		return (1);
	else if (camera_rotate(scene, key))
		return (1);
	else if (key == KEY_Z)
	{
		scene->lvl = MAX(1, scene->lvl - 1);
		*redraw = 3;
	}
	else if (key == KEY_X)
	{
		scene->lvl = MIN(10, scene->lvl + 1);
		*redraw = 3;
	}
	else
		return (0);
	return (1);
}
