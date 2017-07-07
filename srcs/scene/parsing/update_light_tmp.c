/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_light_tmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:12:32 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 16:28:42 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static int	get_light_type(char *type)
{
	if (type)
	{
		if (ft_strstr(type, "base_l"))
			return (BASE_L);
		else if (ft_strstr(type, "point_l"))
			return (POINT_L);
		else if (ft_strstr(type, "dir_l"))
			return (DIR_L);
		else if (ft_strstr(type, "spot_l"))
			return (SPOT_L);
	}
	return ((int)POINT_L);
}

void		update_light_tmp(t_light_tmp **data, char *buf)
{
	if (ft_strstr(buf, "type:"))
		(*data)->type = get_light_type(ft_strchr(buf, ':'));
	else if (ft_strstr(buf, "position"))
		(*data)->position = vector_from_str(buf);
	else if (ft_strstr(buf, "direction"))
		(*data)->vertex = vector_from_str(buf);
	else if (ft_strstr(buf, "color"))
		(*data)->color = color_from_vector(vector_div_d(
											vector_from_str(buf), 255.0));
	else if (ft_strstr(buf, "intensity:"))
		(*data)->intensity = ft_atof(ft_strchr(buf, ':') + 1);
	else if (ft_strstr(buf, "radius:"))
		(*data)->radius = MAX(1, ft_atof(ft_strchr(buf, ':') + 1));
}
