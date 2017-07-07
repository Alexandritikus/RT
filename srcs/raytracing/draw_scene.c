/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:45:34 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 12:14:24 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	cast_ray(t_env *env, double xamnt, double yamnt)
{
	t_ray		view_ray;
	t_color		color;

	color = color_zero();
	view_ray.origin = env->scene->camera->position;
	view_ray.direction = vector_normalize(matrix_to_vector(
		env->scene->camera->view, vector(xamnt, yamnt, -1), 0));
	color = color_add(color, intersect_object(env->scene, view_ray,
		env->scene->max_reflections));
	return (color);
}

static t_color	devide_pixel(t_env *env, int x, int y)
{
	t_vec2	step;
	t_color	rgb_color;
	double	xamnt;
	double	yamnt;
	double	div_lvl;

	div_lvl = 1.0 / (double)env->scene->ssaa;
	rgb_color = color_zero();
	step.y = 0.0;
	while (step.y < 1)
	{
		yamnt = (1 - 2 * ((y + step.y + 0.5) / (double)env->sh)) * ANGLE;
		step.x = 0.0;
		while (step.x < 1)
		{
			xamnt = -(2 * ((x + step.x + 0.5)
				/ (double)env->sw_image) - 1) * ANGLE * env->aspect_ratio;
			rgb_color = color_add(rgb_color, cast_ray(env, xamnt, yamnt));
			step.x += div_lvl;
		}
		step.y += div_lvl;
	}
	return (color_mult(rgb_color, 1.0 / (env->scene->ssaa * env->scene->ssaa)));
}

static void		raytracer(t_env *env, int t_id)
{
	int		x;
	int		y;
	int		int_color;
	int		n;

	n = 0;
	y = t_id;
	while (y < env->sh)
	{
		x = -1;
		while (++x < env->sw_image)
		{
			if (env->scene->antialias)
				int_color = rgb_to_int(clip(devide_pixel(env, x, y)));
			else
				int_color = rgb_to_int(clip(cast_ray(env,
					-(2 * ((x + 0.5) / (double)env->sw_image) - 1) *
													ANGLE * env->aspect_ratio,
					(1 - 2 * ((y + 0.5) / (double)env->sh)) * ANGLE)));
			ft_memcpy(&env->scene->pic->adr[x * 4 +
				y * env->scene->pic->size_line], &int_color, 4);
		}
		y += N_THREAD;
		thread_progress_count(++n, &env->thread_progress);
	}
}

static void		*thread_alloc(void *param)
{
	t_draw	*thread;

	thread = (t_draw*)param;
	raytracer(thread->env, thread->thread_id);
	return (NULL);
}

void			draw_scene(t_env *env)
{
	t_draw		data[N_THREAD];
	pthread_t	t[N_THREAD + 1];
	int			i;

	i = -1;
	while (++i < N_THREAD)
	{
		data[i].thread_id = i;
		data[i].env = env;
	}
	whaiting_message();
	i = -1;
	while (++i < N_THREAD)
		pthread_create(&t[i], NULL, thread_alloc, &data[i]);
	pthread_create(&t[i], NULL, progress_bar, env);
	i = -1;
	while (++i <= N_THREAD)
		pthread_join(t[i], NULL);
	env->thread_progress = 0;
	env->redraw = false;
}
