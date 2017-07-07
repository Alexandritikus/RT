/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_union_tmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:20:38 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 16:29:51 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static int	get_complex_type(char *type)
{
	if (type)
	{
		if (ft_strstr(type, "solid_in"))
			return (SOLID_IN);
		else if (ft_strstr(type, "solid_out"))
			return (SOLID_OUT);
		else if (ft_strstr(type, "compose"))
			return (COMPOSE);
	}
	return (-1);
}

void		update_union_tmp(t_union_tmp **union_data, char *buf)
{
	char	*p;

	if (ft_strstr(buf, "type:"))
		(*union_data)->type = get_complex_type(ft_strchr(buf, ':') + 1);
	else if ((*union_data)->type != -1)
	{
		if (ft_strstr(buf, "position"))
			(*union_data)->orientation.pos = vector_from_str(buf);
		else if (ft_strstr(buf, "rotation"))
			(*union_data)->orientation.rot = vector_mult_d(
												vector_from_str(buf), RAD_COEF);
		else if (ft_strstr(buf, "union_scale"))
			(*union_data)->orientation.scale = vector_from_str(buf);
		else if (ft_strstr(buf, "object_list:"))
		{
			if ((p = ft_strchr(buf, ':') + 1))
				(*union_data)->array = ft_strsplit(p, ' ');
		}
	}
}
