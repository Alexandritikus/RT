/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:42:26 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:42:48 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"
#define BEAM_ANGLE 		30 * RAD_COEF
#define FALL_OFF_ANGLE 	90 * RAD_COEF

static t_color	point_light_color(t_light *light, t_vec light_pos, t_vec point)
{
	double distance_squared;

	distance_squared = pow(dist_to_dot(point, light_pos), 2) * 0.001f;
	return (color(MIN(light->color.r / distance_squared, 1.0f),
			MIN(light->color.g / distance_squared, 1.0f),
			MIN(light->color.b / distance_squared, 1.0f)));
}

static t_color	spot_light_color(t_light *light, t_vec light_pos, t_vec point)
{
	t_vec	to_surface;
	double	angle;
	double	portion;

	to_surface = vector_normalize(vector_sub(point, light_pos));
	angle = acos(vector_dot(to_surface, light->vertex));
	if (angle < BEAM_ANGLE + FALL_OFF_ANGLE)
		return (color_zero());
	if (angle > BEAM_ANGLE)
	{
		portion = 1 - ((angle - BEAM_ANGLE) / FALL_OFF_ANGLE);
		return (color(
				MAX(0, (light->color.r) * portion),
				MAX(0, (light->color.g) * portion),
				MAX(0, (light->color.b) * portion)));
	}
	else
		return (light->color);
}

t_vec			get_position(t_light *l)
{
	double	e1;
	double	e2;
	t_vec	ret;

	e1 = (1.0 / RAND_MAX) * (1.0f * rand());
	e2 = (1.0 / RAND_MAX) * (1.0f * rand());
	ret = matrix_to_vector(disc_rotate(e2 * 360.0, l->normal),
		vector_add(l->position, vector_mult_d(l->perp, e1 * l->radius)), 0);
	return (ret);
}

t_color			get_light_color(t_light *light, t_vec light_pos, t_vec point)
{
	if (light->type == (int)DIR_L || light->type == (int)BASE_L)
		return (light->color);
	else if (light->type == (int)POINT_L)
		return (point_light_color(light, light_pos, point));
	else
		return (spot_light_color(light, light_pos, point));
}

t_vec			get_light_direction(t_light *light, t_vec light_pos, t_vec p)
{
	if (light->type == (int)POINT_L || light->type == (int)BASE_L)
		return (vector_sub(light_pos, p));
	else
		return (light->vertex);
}
