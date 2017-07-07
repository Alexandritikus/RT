/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_from_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:40:44 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/24 10:43:02 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_materials.h"

t_color	color_from_pixel(t_img *pic, int x, int y)
{
	t_color	color;
	int		r;
	int		g;
	int		b;
	int		f;

	color = color_zero();
	if (x >= 0 && x < pic->width && y >= 0 && y < pic->height)
	{
		b = pic->adr[x * 4 + y * pic->size_line];
		g = pic->adr[x * 4 + y * pic->size_line + 1];
		r = pic->adr[x * 4 + y * pic->size_line + 2];
		f = pic->adr[x * 4 + y * pic->size_line + 3];
		color.r = (double)(r >= 0 ? r : 256 + r) / 255.0;
		color.g = (double)(g >= 0 ? g : 256 + g) / 255.0;
		color.b = (double)(b >= 0 ? b : 256 + b) / 255.0;
		color.f = (double)f;
	}
	return (color);
}
