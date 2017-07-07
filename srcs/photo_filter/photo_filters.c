/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photo_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:40:11 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 09:52:14 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		use_filter_func(t_color rgb_col, t_color av_color, t_env *env)
{
	if (env->scene->filter == GREYSCALE)
		return (use_grey_scale(rgb_col));
	if (env->scene->filter == NEGATIVE)
		return (use_negative(rgb_col));
	if (env->scene->filter == B_W)
		return (use_black_and_white(rgb_col, av_color));
	if (env->scene->filter == SEPIA)
		return (use_sepia(rgb_col));
	if (env->scene->filter == WARM)
		return (use_warm(rgb_col));
	return (0);
}

static t_color	get_av_color(t_img *pic)
{
	t_color		av_color;
	t_color		cur_col;
	t_vec_i2	xy;
	int			bws;

	bws = 0;
	xy.y = -1;
	av_color = color_zero();
	while (++xy.y < pic->height)
	{
		xy.x = -1;
		while (++xy.x < pic->width)
		{
			cur_col = color_from_pixel(pic, xy.x, xy.y);
			if (rgb_to_int(cur_col) == BLACK
				|| rgb_to_int(cur_col) == WHITE)
				bws++;
			else
				av_color = color_add(av_color, cur_col);
		}
	}
	av_color = color_mult(av_color, (1.0 / (pic->height * pic->width - bws)));
	return (av_color);
}

static int		sample_linear(t_img *dest, t_env *src, int x, int y)
{
	t_color		sampler;
	int			samples;
	int			m_blur;

	sampler = color_zero();
	samples = 0;
	m_blur = 0;
	while (m_blur < src->scene->m_blur_k && x < dest->width)
	{
		sampler = color_add(sampler, color_from_pixel(src->scene->pic, ++x, y));
		samples++;
		m_blur++;
	}
	if (samples > 0)
		sampler = color_mult(sampler, 1.0 / samples);
	return (rgb_to_int(sampler));
}

static void		iterate(t_img *pic, t_env *env)
{
	t_vec_i2	xy;
	t_color		av_color;
	t_color		color_rgb;
	int			color_i;

	xy.y = 0;
	av_color = get_av_color(pic);
	while (xy.y < pic->height)
	{
		xy.x = 0;
		while (xy.x < pic->width)
		{
			color_rgb = color_from_pixel(pic, xy.x, xy.y);
			if (env->scene->filter != MOTION_BLUR)
				color_i = use_filter_func(color_rgb, av_color, env);
			else
				color_i = sample_linear(pic, env, xy.x, xy.y);
			ft_memcpy(&pic->adr[xy.x * 4 +
				xy.y * pic->size_line], &color_i, 4);
			xy.x++;
		}
		xy.y++;
	}
}

void			use_photo_filter(t_env *env)
{
	int		len;

	if (env->scene->filter != NONE)
	{
		len = env->sh * env->sw_image * 4 - 1;
		while (len)
		{
			env->filter->adr[len] = env->scene->pic->adr[len];
			len--;
		}
		iterate(env->filter, env);
		mlx_put_image_to_window(env->mlx, env->win, env->filter->img, 0, 0);
	}
}
