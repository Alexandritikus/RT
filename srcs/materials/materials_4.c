/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 10:56:11 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 11:47:21 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

t_material	fix_material(t_material material)
{
	material.is_normal = (material.type == (int)AIR ?
								false : material.is_normal);
	material.shininess = ((material.type == (int)AIR ||
							material.type == (int)FLATCOLOR) ||
							material.texture || material.bump_map ?
								NOT_SHINY : material.shininess);
	material.reflectivity = ((material.type == (int)AIR ||
								material.type == (int)FLATCOLOR) ||
								material.texture || material.bump_map ?
								NOT_REFLECTIVE : material.reflectivity);
	material.refractive = (material.type == (int)GLASS ||
							material.bump_map ?
							material.refractive : NOT_REFRACTIVE);
	if (material.texture && !material.bump_map &&
					(material.slide || material.cut || material.trans_mod))
	{
		material.type = GLASS;
		material.refractive = 1;
		material.reflectivity = NOT_REFLECTIVE;
	}
	else if (material.bump_map)
		material.type = FLATCOLOR;
	return (material);
}
