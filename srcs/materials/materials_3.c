/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:22:24 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 16:48:57 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

static t_color	return_criscol(t_mat_tmp data, t_material material)
{
	t_color	color1;
	t_color	color2;
	t_color	color3;

	color1 = color_mult(color_add(color_mult(material.color1, data.coef_a),
		color_mult(material.color2, (1.0 - data.coef_a))), 0.25);
	color2 = color_mult(color_add(color_mult(material.color2, data.coef_b),
		color_mult(material.color3, (1.0 - data.coef_b))), 0.25);
	color3 = color_mult(color_add(color_mult(material.color3, data.coef_c),
		color_mult(material.color1, (1.0 - data.coef_c))), 0.25);
	return (color_add(color_add(color1, color2), color3));
}

t_color			get_crisscross_color(t_material material, t_vec point)
{
	t_mat_tmp	data;

	data.x = point.x * material.scale * 0.5;
	data.y = point.y * material.scale * 0.5;
	data.z = point.z * material.scale * 0.5;
	data.coef_a = 0;
	data.coef_b = 0;
	data.coef_c = 0;
	data.level = 0;
	while (++data.level < 10)
	{
		data.coef_a += (1.0 / data.level) * fabs(noise(material.perlin,
			data.level * 0.35 * data.x, data.level * 0.05 * data.y,
			data.level * data.z));
		data.coef_b += (1.0 / data.level) * fabs(noise(material.perlin,
			data.level * data.x, data.level * 0.35 * data.y,
			data.level * 0.05 * data.z));
		data.coef_c += (1.0 / data.level) * fabs(noise(material.perlin,
			data.level * 0.05 * data.x, data.level * data.y,
			data.level * 0.35 * data.z));
	}
	data.coef_a = 0.5 * sin((data.x + data.z) * 0.05 + data.coef_a) + 0.5;
	data.coef_b = 0.5 * sin((data.y + data.x) * 0.05 + data.coef_b) + 0.5;
	data.coef_c = 0.5 * sin((data.z + data.y) * 0.05 + data.coef_c) + 0.5;
	return (return_criscol(data, material));
}
