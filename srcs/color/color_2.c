/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:29:21 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:35:52 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_color.h"
#include "libft.h"

int		rgb_to_int(t_color color)
{
	return ((int)(color.r * 255) << 16 |
			(int)(color.g * 255) << 8 |
			(int)(color.b * 255));
}

t_color	clip(t_color color)
{
	const double	allight = color.r + color.g + color.b;
	const double	excesslight = allight - 3;
	t_color			result;

	result = color;
	if (excesslight > 0)
	{
		result.r = result.r + excesslight * (result.r / allight);
		result.g = result.g + excesslight * (result.g / allight);
		result.b = result.b + excesslight * (result.b / allight);
	}
	result.r = MIN(1, MAX(result.r, 0));
	result.g = MIN(1, MAX(result.g, 0));
	result.b = MIN(1, MAX(result.b, 0));
	return (result);
}

t_color	color_from_vector(t_vec vec)
{
	t_color	color;

	color.r = MIN(1, MAX(vec.x, 0.0));
	color.g = MIN(1, MAX(vec.y, 0.0));
	color.b = MIN(1, MAX(vec.z, 0.0));
	color.f = 1.0;
	return (color);
}

t_color	color_mult_color(t_color col1, t_color col2)
{
	t_color	color;

	color.r = col1.r * col2.r;
	color.g = col1.g * col2.g;
	color.b = col1.b * col2.b;
	return (color);
}
