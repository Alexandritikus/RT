/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_part_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:25:33 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 16:49:24 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = ((h < 8) || (h == 12) || (h == 13)) ? x : y;
	v = ((h < 4) || (h == 12) || (h == 13)) ? y : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double			noise(t_noise perlin, double x, double y, double z)
{
	t_noise_tmp	data;

	data.xx = (int)floor(x) & 255;
	data.yy = (int)floor(y) & 255;
	data.zz = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	data.u = fade(x);
	data.v = fade(y);
	data.w = fade(z);
	data.a = perlin.noise[data.xx] + data.yy;
	data.aa = perlin.noise[data.a] + data.zz;
	data.ab = perlin.noise[data.a + 1] + data.zz;
	data.b = perlin.noise[data.xx + 1] + data.yy;
	data.ba = perlin.noise[data.b] + data.zz;
	data.bb = perlin.noise[data.b + 1] + data.zz;
	return (lerp(data.w, lerp(data.v, lerp(data.u, grad(perlin.noise[data.aa],
		x, y, z), grad(perlin.noise[data.ba], x - 1, y, z)), lerp(data.u,
		grad(perlin.noise[data.ab], x, y - 1, z), grad(perlin.noise[data.bb],
		x - 1, y - 1, z))), lerp(data.v, lerp(data.u,
		grad(perlin.noise[data.aa + 1], x, y, z - 1),
		grad(perlin.noise[data.ba + 1], x - 1, y, z - 1)),
		lerp(data.u, grad(perlin.noise[data.ab + 1], x, y - 1, z - 1),
		grad(perlin.noise[data.bb + 1], x - 1, y - 1, z - 1)))));
}
