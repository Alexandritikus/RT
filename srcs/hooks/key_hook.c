/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:48:34 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 11:44:20 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	key_up_top(t_env *env, int key)
{
	if (key == KEY_R)
		env->redraw = 2;
	else if (key == KEY_F2)
		env->scene->effects = !env->scene->effects;
	else if (key == KEY_F1)
		env->scene->antialias = !env->scene->antialias;
	else if (key == KEY_PAD_SUB)
	{
		if (env->scene->ssaa > 1)
			env->scene->ssaa--;
	}
	else if (key == KEY_PAD_ADD)
	{
		if (env->scene->ssaa < 4)
			env->scene->ssaa++;
	}
	else if (key == KEY_B)
	{
		env->scene->m_blur_k++;
		if (env->scene->m_blur_k > 50)
			env->scene->m_blur_k = 1;
	}
	else
		return (0);
	return (1);
}

static void	change_mode(t_env *env)
{
	if (env->mode == MODE_VIEW)
		env->mode = MODE_CREATE;
	else if (env->mode == MODE_CREATE)
	{
		env->mode = MODE_VIEW;
		env->scene->active = NULL;
	}
	env->redraw = 3;
}

static void	create_mode(int key, t_env *env)
{
	if (key_up_top(env, key))
		env->redraw = (env->redraw == 2 ? 2 : 3);
	else if (key_middle_top(env, key))
		env->redraw = 3;
	else if (key_camera(env->scene, key, &env->redraw))
		env->redraw = (env->redraw == 3 ? 3 : 2);
	else if (key_creative(env, key))
		env->redraw = (env->redraw == 2 ? 2 : 3);
	else if (key == KEY_PAD_5)
		dublicate_image(env);
	else if (key == KEY_F8 && env->active == 2)
	{
		show_stereo(env);
		env->redraw = 3;
	}
}

int			key_hook(int key, t_env *env)
{
	if (key == KEY_ESCAPE)
	{
		delete_environment(env);
		exit(1);
	}
	else if (env->mode <= MODE_PIC_LIST)
		return (0);
	else if (key == KEY_F3)
		create_img_file((env->scene->filter == NONE ?
												env->scene->pic : env->filter));
	else if (key == KEY_F4)
		change_mode(env);
	else if (env->mode == (int)MODE_CREATE)
		create_mode(key, env);
	expose_hook(env);
	return (0);
}
