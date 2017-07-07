/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:31:42 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/15 12:32:46 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"
#include <stdlib.h>

t_material	material_base(void)
{
	t_material	material;

	material.type = SHINYCOLOR;
	material.is_normal = false;
	material.slide = false;
	material.cut = false;
	material.trans_mod = 0;
	material.perlin = perlin_noise();
	material.color1 = color(1.0, 1.0, 1.0);
	material.color2 = color_zero();
	material.color3 = color_zero();
	material.scale = 0;
	material.shininess = 100;
	material.reflectivity = NOT_REFLECTIVE;
	material.refractive = NOT_REFRACTIVE;
	material.bump_scale = 0.0;
	material.texture = NULL;
	material.bump_map = NULL;
	return (material);
}

t_vec		mater_modify_normal(t_material mat, t_vec normal, t_vec point)
{
	if (mat.is_normal)
		return (map_modify_normal(mat.normal_map, normal, point));
	else
		return (normal);
}

double		get_shininess(t_material mat)
{
	if (mat.type == (int)AIR || mat.type == (int)FLATCOLOR)
		return (NOT_SHINY);
	else
		return (mat.shininess);
}

double		get_reflectivity(t_material mat)
{
	if (mat.type == (int)AIR ||
		mat.type == (int)FLATCOLOR ||
		mat.type == (int)GLASS)
		return (NOT_REFLECTIVE);
	else
		return (mat.reflectivity);
}

double		get_refractive(t_material mat)
{
	if (mat.type == (int)AIR)
		return (AIR_REFRACTIVE_INDEX);
	else if (mat.type == (int)GLASS)
		return (mat.refractive);
	else
		return (NOT_REFRACTIVE);
}
