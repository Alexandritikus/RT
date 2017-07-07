/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_environment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:33:28 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 11:38:52 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delete_environment(t_env *env)
{
	t_scene	*current_scene;

	if (env)
	{
		mlx_destroy_image(env->mlx, env->title);
		mlx_destroy_image(env->mlx, env->pic_list);
		mlx_destroy_image(env->mlx, env->menu);
		delete_image(&env->filter, env->filter->img, env->mlx);
		delete_image(&env->dublicate_1, env->dublicate_1->img, env->mlx);
		delete_image(&env->dublicate_2, env->dublicate_2->img, env->mlx);
		mlx_destroy_window(env->mlx, env->win);
		if (env->scene)
		{
			current_scene = env->scene;
			while (current_scene)
			{
				env->scene = env->scene->next;
				delete_scene(&current_scene, env->mlx);
				current_scene = env->scene;
			}
		}
		free(env->mlx);
		free(env);
	}
}
