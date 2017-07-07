/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photo_filters_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtiterin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:54:06 by vtiterin          #+#    #+#             */
/*   Updated: 2017/06/26 16:54:16 by vtiterin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		use_grey_scale(t_color color_rgb)
{
	double		av;

	av = (color_rgb.r + color_rgb.g + color_rgb.b) / 3;
	color_rgb = color(av, av, av);
	return (rgb_to_int(color_rgb));
}

int		use_negative(t_color color_rgb)
{
	color_rgb = color(1.0 - color_rgb.r
		, 1.0 - color_rgb.g, 1.0 - color_rgb.b);
	return (rgb_to_int(color_rgb));
}

int		use_black_and_white(t_color rgb_col, t_color av_color)
{
	int		color_i;
	int		av_color_i;

	color_i = rgb_to_int(rgb_col);
	av_color_i = rgb_to_int(av_color);
	if (color_i < av_color_i)
		return (BLACK);
	else if (color_i > av_color_i)
		return (WHITE);
	else
		return (GREY);
}

int		use_sepia(t_color rgb)
{
	t_color		new_col;

	new_col.r = (rgb.r * 0.393) + (rgb.g * 0.769) + (rgb.b * 0.189);
	new_col.g = (rgb.r * 0.349) + (rgb.g * 0.686) + (rgb.b * 0.168);
	new_col.b = (rgb.r * 0.272) + (rgb.g * 0.534) + (rgb.b * 0.131);
	return (rgb_to_int(clip(new_col)));
}

int		use_warm(t_color rgb)
{
	double		av;

	av = (rgb.r + rgb.g + rgb.b) / 3;
	if (av <= 1.0)
		rgb = color(1.0, 0.0, 0.0);
	if (av <= (1.0 / 5) * 4)
		rgb = color(1.0, 1.0, 0.0);
	if (av <= (1.0 / 5) * 3)
		rgb = color(0.0, 1.0, 1.0);
	if (av <= (1.0 / 5) * 2)
		rgb = color(1.0, 0.0, 1.0);
	if (av <= (1.0 / 5))
		rgb = color(0.0, 0.0, 1.0);
	return (rgb_to_int(clip(rgb)));
}
