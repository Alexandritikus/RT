/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:03:35 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 16:30:14 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			expose_hook(t_env *env)
{
	if (env->redraw != 0)
	{
		if (env->mode <= MODE_PIC_LIST && env->scene)
			env->scene->filter = NONE;
		if (env->redraw < 3)
			mlx_clear_window(env->mlx, env->win);
		if (env->mode == (int)MODE_TITLE)
			mlx_put_image_to_window(env->mlx, env->win, env->title, 0, 0);
		else if (env->mode == (int)MODE_PIC_LIST)
			mlx_put_image_to_window(env->mlx, env->win, env->pic_list, 0, 0);
		else if (env->scene)
		{
			if (env->redraw == 2)
				draw_scene(env);
			if (env->redraw < 3)
				mlx_put_image_to_window(env->mlx, env->win,
													env->scene->pic->img, 0, 0);
		}
		if (env->mode > MODE_PIC_LIST && env->scene)
			print_menu(env);
		env->redraw = 0;
	}
	return (0);
}
