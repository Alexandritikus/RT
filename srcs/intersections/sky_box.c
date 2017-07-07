/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:52:40 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/12 17:23:57 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static t_color	sky_box_color(t_img *bg, double u, double v)
{
	double	di;
	double	dj;
	int		i1;
	int		j1;

	di = u * (double)(bg->width - 1);
	dj = (1.0 - v) * (double)(bg->height - 1);
	i1 = ((di + 1) >= bg->width) ? 0 : di + 1;
	j1 = ((dj + 1) >= bg->height) ? 0 : dj + 1;
	return (color_from_pixel(bg, i1, j1));
}

static t_color	bg_l_r(t_scene *scene, t_ray ray)
{
	double	u;
	double	v;

	if (ray.direction.x > 0.0f)
	{
		u = 1.0f - (ray.direction.z / ray.direction.x + 1.0f) * 0.5f;
		v = (ray.direction.y / ray.direction.x + 1.0f) * 0.5f;
		return (sky_box_color(scene->bg->right, u, v));
	}
	else if (ray.direction.x < 0.0f)
	{
		u = 1.0f - (ray.direction.z / ray.direction.x + 1.0f) * 0.5f;
		v = 1.0f - (ray.direction.y / ray.direction.x + 1.0f) * 0.5f;
		return (sky_box_color(scene->bg->left, u, v));
	}
	return (color_zero());
}

static t_color	bg_t_b(t_scene *scene, t_ray ray)
{
	double	u;
	double	v;

	if (ray.direction.y > 0.0f)
	{
		u = (ray.direction.x / ray.direction.y + 1.0f) * 0.5f;
		v = 1.0f - (ray.direction.z / ray.direction.y + 1.0f) * 0.5f;
		return (sky_box_color(scene->bg->top, u, v));
	}
	else if (ray.direction.y < 0.0f)
	{
		u = 1.0f - (ray.direction.x / ray.direction.y + 1.0f) * 0.5f;
		v = (ray.direction.z / ray.direction.y + 1.0f) * 0.5f;
		return (sky_box_color(scene->bg->bottom, u, v));
	}
	return (color_zero());
}

static t_color	bg_f_b(t_scene *scene, t_ray ray)
{
	double	u;
	double	v;

	if (ray.direction.z > 0.0f)
	{
		u = (ray.direction.x / ray.direction.z + 1.0f) * 0.5f;
		v = (ray.direction.y / ray.direction.z + 1.0f) * 0.5f;
		return (sky_box_color(scene->bg->front, u, v));
	}
	else if (ray.direction.z < 0.0f)
	{
		u = (ray.direction.x / ray.direction.z + 1.0f) * 0.5f;
		v = 1.0f - (ray.direction.y / ray.direction.z + 1) * 0.5f;
		return (sky_box_color(scene->bg->back, u, v));
	}
	return (color_zero());
}

t_color			bg_color(t_scene *scene, t_ray ray)
{
	t_color	color;

	color = scene->bg_color;
	if (scene->bg == NULL)
		return (color);
	if ((fabs(ray.direction.x) >= fabs(ray.direction.y)) &&
					(fabs(ray.direction.x) >= fabs(ray.direction.z)))
		color = bg_l_r(scene, ray);
	else if ((fabs(ray.direction.y) >= fabs(ray.direction.x)) &&
					(fabs(ray.direction.y) >= fabs(ray.direction.z)))
		color = bg_t_b(scene, ray);
	else if ((fabs(ray.direction.z) >= fabs(ray.direction.x)) &&
					(fabs(ray.direction.z) >= fabs(ray.direction.y)))
		color = bg_f_b(scene, ray);
	return (color);
}
