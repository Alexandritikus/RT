/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtiterin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:43:15 by vtiterin          #+#    #+#             */
/*   Updated: 2017/06/26 16:43:17 by vtiterin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

bool	check_texture_param(t_material material, t_color obj_col)
{
	if (material.slide)
		return (false);
	else if (material.cut)
	{
		if (obj_col.r != 0.0 && obj_col.g != 0.0 && obj_col.b != 0.0)
			return (true);
	}
	else if (material.trans_mod)
	{
		if (material.trans_mod == (int)M_R && obj_col.r < ACCURACY)
			return (true);
		else if (material.trans_mod == (int)M_G && obj_col.g < ACCURACY)
			return (true);
		else if (material.trans_mod == (int)M_B && obj_col.b < ACCURACY)
			return (true);
	}
	return (false);
}
