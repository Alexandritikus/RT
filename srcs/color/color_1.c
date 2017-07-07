/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:07:02 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:33:44 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_color.h"

t_color	color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.f = 1.0;
	return (color);
}

t_color	color_zero(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.f = 1.0;
	return (color);
}

t_color	color_full(double r, double g, double b, double f)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.f = f;
	return (color);
}

t_color	color_mult(t_color col, double amount)
{
	t_color	color;

	color = color_zero();
	color.r = col.r * amount;
	color.g = col.g * amount;
	color.b = col.b * amount;
	return (color);
}

t_color	color_add(t_color col1, t_color col2)
{
	t_color	color;

	color = color_zero();
	color.r = NTZ(col2.r) + NTZ(col1.r);
	color.g = NTZ(col2.g) + NTZ(col1.g);
	color.b = NTZ(col2.b) + NTZ(col1.b);
	return (color);
}
