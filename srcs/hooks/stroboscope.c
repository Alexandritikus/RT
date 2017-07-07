/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stroboscope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:25:31 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 11:54:32 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	dublicate(char *adr, t_env *env)
{
	int	len;

	len = env->sh * env->sw_image * 4 - 1;
	while (len)
	{
		adr[len] = env->scene->pic->adr[len];
		len--;
	}
}

static void	delete_red(t_img *pic)
{
	int		x;
	int		y;
	int		color_i;
	t_color	color_rgb;

	y = 0;
	while (y < pic->height)
	{
		x = 0;
		while (x < pic->width)
		{
			color_rgb = color_from_pixel(pic, x, y);
			color_i = rgb_to_int(color(0, color_rgb.g, color_rgb.b));
			color_i = color_i + ((int)(0.5 * 255) << 24);
			ft_memcpy(&pic->adr[x * 4 + y * pic->size_line], &color_i, 4);
			x++;
		}
		y++;
	}
}

static void	delete_green_blue(t_img *pic)
{
	int		x;
	int		y;
	int		color_i;
	t_color	color_rgb;

	y = 0;
	while (y < pic->height)
	{
		x = 0;
		while (x < pic->width)
		{
			color_rgb = color_from_pixel(pic, x, y);
			color_i = rgb_to_int(color(color_rgb.r, 0, 0));
			color_i = color_i + ((int)(0.5 * 255) << 24);
			ft_memcpy(&pic->adr[x * 4 + y * pic->size_line], &color_i, 4);
			x++;
		}
		y++;
	}
}

void		dublicate_image(t_env *env)
{
	if (env->active == 0)
	{
		dublicate(env->dublicate_1->adr, env);
		delete_red(env->dublicate_1);
		env->active++;
	}
	else if (env->active == 1)
	{
		dublicate(env->dublicate_2->adr, env);
		delete_green_blue(env->dublicate_2);
		env->active++;
	}
}

int			show_stereo(t_env *env)
{
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->dublicate_1->img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->win, env->dublicate_2->img, 0, 0);
	env->active = 0;
	return (0);
}
