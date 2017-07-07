/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_creative_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:39:32 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 11:35:56 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	change_r_color(t_object *active, int key)
{
	t_color		*color;

	if (active->color == COLOR_1)
		color = &active->material.color1;
	if (active->color == COLOR_2)
		color = &active->material.color2;
	if (active->color == COLOR_3)
		color = &active->material.color3;
	if (key == KEY_PAD_7)
	{
		if (color->r < 1.0)
			color->r += 0.05;
	}
	if (key == KEY_PAD_1)
	{
		if (color->r > 0.0)
			color->r -= 0.05;
	}
}

static void	change_g_color(t_object *active, int key)
{
	t_color		*color;

	if (active->color == COLOR_1)
		color = &active->material.color1;
	if (active->color == COLOR_2)
		color = &active->material.color2;
	if (active->color == COLOR_3)
		color = &active->material.color3;
	if (key == KEY_PAD_8)
	{
		if (color->g < 1.0)
			color->g += 0.05;
	}
	if (key == KEY_PAD_2)
	{
		if (color->g > 0.0)
			color->g -= 0.05;
	}
}

static void	change_b_color(t_object *active, int key)
{
	t_color		*color;

	if (active->color == COLOR_1)
		color = &active->material.color1;
	if (active->color == COLOR_2)
		color = &active->material.color2;
	if (active->color == COLOR_3)
		color = &active->material.color3;
	if (key == KEY_PAD_9)
	{
		if (color->b < 1.0)
			color->b += 0.05;
	}
	if (key == KEY_PAD_3)
	{
		if (color->b > 0.0)
			color->b -= 0.05;
	}
}

int			color_manipulate(t_object *active, int key, int *redraw)
{
	if (key == KEY_PAD_4 && active->color > 1)
		active->color -= 1;
	else if (key == KEY_PAD_6 && active->color < 3)
		active->color += 1;
	else if (key == KEY_PAD_7 || key == KEY_PAD_1)
	{
		change_r_color(active, key);
		*redraw = 2;
	}
	else if (key == KEY_PAD_8 || key == KEY_PAD_2)
	{
		change_g_color(active, key);
		*redraw = 2;
	}
	else if (key == KEY_PAD_9 || key == KEY_PAD_3)
	{
		change_b_color(active, key);
		*redraw = 2;
	}
	else
		return (0);
	return (1);
}
