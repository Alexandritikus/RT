/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:41:46 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/05 12:53:49 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void	update_color(t_material *material, char *buf)
{
	if (ft_strstr(buf, "color_1"))
		material->color1 = color_from_vector(vector_div_d(
			vector_from_str(ft_strchr(buf, '(')), 255.0));
	else if (ft_strstr(buf, "color_2"))
		material->color2 = color_from_vector(vector_div_d(
			vector_from_str(ft_strchr(buf, '(')), 255.0));
	else if (ft_strstr(buf, "color_3"))
		material->color3 = color_from_vector(vector_div_d(
			vector_from_str(ft_strchr(buf, '(')), 255.0));
}

static int	texture_type(char *type)
{
	if (ft_strstr(type, "checkboard"))
		return (CHECKBOARD);
	else if (ft_strstr(type, "crisscross"))
		return (CRISSCROSS);
	else if (ft_strstr(type, "glass"))
		return (GLASS);
	else if (ft_strstr(type, "marble"))
		return (MARBLE);
	else if (ft_strstr(type, "shinycolor"))
		return (SHINYCOLOR);
	else if (ft_strstr(type, "turbulence"))
		return (TURBULENCE);
	else if (ft_strstr(type, "wood"))
		return (WOOD);
	else if (ft_strstr(type, "flatcolor"))
		return (FLATCOLOR);
	else
		return (AIR);
}

static int	texture_transparency(char *type)
{
	if (ft_strstr(type, "red"))
		return (M_R);
	else if (ft_strstr(type, "green"))
		return (M_G);
	else if (ft_strstr(type, "blue"))
		return (M_B);
	else
		return (0);
}

static void	update_texture(t_material *material, char *buf, void *mlx)
{
	if (material->texture == NULL && ft_strstr(buf, "texture_img"))
		material->texture = texture_from_file(buf, mlx);
	else if (material->texture)
	{
		if (ft_strstr(buf, "texture_slide"))
			material->slide = (ft_strstr(buf, "true") ? true : false);
		else if (!material->slide && ft_strstr(buf, "texture_cut"))
			material->cut = (ft_strstr(buf, "true") ? true : false);
		else if (!material->slide && ft_strstr(buf, "texture_trans"))
			material->trans_mod = texture_transparency(buf);
	}
	if (material->bump_map == NULL && ft_strstr(buf, "texture_bump"))
		material->bump_map = texture_from_file(buf, mlx);
	else if (material->bump_map && ft_strstr(buf, "bump_scale:"))
		material->bump_scale = MAX(0.0, ft_atof(ft_strchr(buf, ':') + 1));
}

void		update_material(t_material *material, char *buf, void *mlx)
{
	update_color(material, buf);
	if (ft_strstr(buf, "texture_type:"))
		material->type = texture_type(ft_strchr(buf, ':') + 1);
	else if (ft_strstr(buf, "texture_scale:"))
		material->scale = MAX(ACCURACY, ft_atof(ft_strchr(buf, ':') + 1));
	else if (ft_strstr(buf, "shininess:"))
		material->shininess = ft_atof(ft_strchr(buf, ':') + 1);
	else if (ft_strstr(buf, "reflectivity:"))
		material->reflectivity = MIN(1, MAX(ACCURACY,
											ft_atof(ft_strchr(buf, ':') + 1)));
	else if (ft_strstr(buf, "refractive:"))
		material->refractive = MAX(1, ft_atof(ft_strchr(buf, ':') + 1));
	else if (ft_strstr(buf, "normal_map"))
	{
		material->is_normal = true;
		material->normal_map = normal_map(ft_atof(ft_strchr(buf, '(') + 1),
											ft_atof(ft_strchr(buf, ',') + 1));
	}
	else
		update_texture(material, buf, mlx);
}
