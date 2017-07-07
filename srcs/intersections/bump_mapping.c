/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:29:47 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/07 15:39:09 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static double	bump_color(t_intersect inter, double u, double v)
{
	double	di;
	double	dj;
	int		i1;
	int		j1;

	di = (1.0 - u) * (double)(inter.obj->material.bump_map->width - 1);
	dj = (1.0 - v) * (double)(inter.obj->material.bump_map->height - 1);
	i1 = (((int)di + 1) >= inter.obj->material.bump_map->width) ? 0 :
															(int)di + 1;
	j1 = (((int)dj + 1) >= inter.obj->material.bump_map->height) ? 0 :
															(int)dj + 1;
	return ((1 - (di - (int)di)) * (1 - (dj - (int)dj)) *
				inter.obj->material.bump_map->adr[(int)di *
				4 + (int)dj * inter.obj->material.bump_map->size_line + 2] +
			(1 - (di - (int)di)) * ((dj - (int)dj)) *
				inter.obj->material.bump_map->adr[(int)di *
				4 + j1 * inter.obj->material.bump_map->size_line + 2] +
			((di - (int)di)) * (1 - (dj - (int)dj)) *
				inter.obj->material.bump_map->adr[i1 *
				4 + (int)dj * inter.obj->material.bump_map->size_line + 2] +
			((di - (int)di)) * ((dj - (int)dj)) *
				inter.obj->material.bump_map->adr[i1 *
				4 + j1 * inter.obj->material.bump_map->size_line + 2]);
}

t_vec			bump(t_intersect inter)
{
	double	e;
	double	fu;
	double	fv;
	t_vec	d;

	e = DBL_EPSILON;
	fu = (bump_color(inter, inter.u + e, inter.v) -
				bump_color(inter, inter.u - e, inter.v)) / (2 * e);
	fv = (bump_color(inter, inter.u, inter.v + e) -
				bump_color(inter, inter.u, inter.v - e)) / (2 * e);
	d = vector_mult_d(vector_sub(vector_mult_d(
				vector_cross(inter.normal, inter.pv), fu),
				vector_mult_d(vector_cross(inter.normal, inter.pu), fv)),
				inter.obj->material.bump_scale / vector_length(inter.normal));
	return (vector_normalize(vector_add(inter.normal, d)));
}
