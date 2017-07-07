/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene_tmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:31:20 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 16:29:26 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void	update_scene_tmp_two(t_scene_tmp **data, char *buf)
{
	if (ft_strstr(buf, "bg_color"))
		(*data)->bg_color = color_from_vector(vector_div_d(
			vector_from_str(ft_strchr(buf, '(')), 255.0));
}

void		update_scene_tmp(t_scene_tmp **data, char *buf, void *mlx)
{
	if (ft_strstr(buf, "effects"))
		(*data)->effects = (ft_strstr(buf, "true") ? true : false);
	else if (ft_strstr(buf, "ssaa:"))
		(*data)->ssaa = MAX(1, ft_atoi(ft_strchr(buf, ':') + 1));
	else if (ft_strstr(buf, "max_reflections:"))
		(*data)->max_reflections = MAX(1, ft_atoi(ft_strchr(buf, ':') + 1));
	else if (ft_strstr(buf, "shadow_samples:"))
		(*data)->shadow_samples = MAX(1, ft_atoi(ft_strchr(buf, ':') + 1));
	else if (ft_strstr(buf, "camera_position"))
		(*data)->cam_position = vector_from_str(buf);
	else if (ft_strstr(buf, "camera_look_at"))
		(*data)->cam_look_at = vector_from_str(buf);
	else if (ft_strstr(buf, "camera_rotation"))
		(*data)->cam_rotation = vector_mult_d(vector_from_str(buf), RAD_COEF);
	else if (ft_strstr(buf, "sky_box") && (*data)->bg == NULL)
	{
		if (((*data)->sky_box_link = ft_link_from_str(buf)) != NULL)
		{
			(*data)->bg = get_sky_box((*data)->sky_box_link, mlx);
			free((*data)->sky_box_link);
			(*data)->sky_box_link = NULL;
		}
	}
	else
		update_scene_tmp_two(data, buf);
}
