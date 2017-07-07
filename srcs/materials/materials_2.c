/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:53:50 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 16:52:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"
#define POINT_OFFSET 3893343

t_color	get_afgs_color(t_material material, t_vec point)
{
	if (point.x)
		return (material.color1);
	else
		return (material.color1);
}

t_color	get_checkerboard_color(t_material material, t_vec point)
{
	int x;
	int y;
	int z;

	if ((int)((point.x + POINT_OFFSET) / material.scale) % 2 == 0)
		x = 1;
	else
		x = 0;
	if ((int)((point.y + POINT_OFFSET) / material.scale) % 2 == 0)
		y = 1;
	else
		y = 0;
	if ((int)((point.z + POINT_OFFSET) / material.scale) % 2 == 0)
		z = 1;
	else
		z = 0;
	if ((x ^ y) ^ z)
		return (material.color1);
	else
		return (material.color2);
}

t_color	get_marble_color(t_material material, t_vec point)
{
	double	x;
	double	y;
	double	z;
	double	noise_coef;
	int		level;

	x = point.x * material.scale;
	y = point.y * material.scale;
	z = point.z * material.scale;
	noise_coef = 0;
	level = 0;
	while (++level < 10)
		noise_coef += (1.0 / level) * fabs(noise(material.perlin,
												level * 0.05 * x,
												level * 0.15 * y,
												level * 0.05 * z));
	noise_coef = 0.5 * sin((x + y) * 0.05 + noise_coef) + 0.5;
	return (color_add(color_mult(material.color1, noise_coef),
		color_mult(material.color2, (1.0 - noise_coef))));
}

t_color	get_turbulence_color(t_material material, t_vec point)
{
	double	x;
	double	y;
	double	z;
	double	noise_coef;
	int		level;

	x = point.x * material.scale;
	y = point.y * material.scale;
	z = point.z * material.scale;
	noise_coef = 0;
	level = 0;
	while (++level < 10)
		noise_coef += (1.0 / level) * fabs(noise(material.perlin,
												level * 0.05 * x,
												level * 0.05 * y,
												level * 0.05 * z));
	return (color_add(color_mult(material.color1, noise_coef),
		color_mult(material.color2, (1.0 - noise_coef))));
}

t_color	get_wood_color(t_material material, t_vec point)
{
	double	x;
	double	y;
	double	z;
	double	grain;

	x = point.x * material.scale;
	y = point.y * material.scale;
	z = point.z * material.scale;
	grain = noise(material.perlin, x, y, z) * 5;
	grain = grain - (int)grain;
	return (color_add(color_mult(material.color1, grain),
		color_mult(material.color2, (1.0 - grain))));
}
