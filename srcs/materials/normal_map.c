/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:59:57 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 16:49:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

t_norm_map		normal_map(double scale, double amount)
{
	t_norm_map	map;

	map.perlin = perlin_noise();
	map.scale = scale;
	map.amount = amount;
	return (map);
}

t_vec			map_modify_normal(t_norm_map map, t_vec normal, t_vec point)
{
	t_vec	noisee;
	double	x;
	double	y;
	double	z;

	x = point.x / map.scale;
	y = point.y / map.scale;
	z = point.z / map.scale;
	noisee.x = noise(map.perlin, x, y, z);
	noisee.y = noise(map.perlin, y, z, x);
	noisee.z = noise(map.perlin, z, x, y);
	return (vector_normalize(vector_add(normal,
			vector_mult_d(noisee, map.amount))));
}
