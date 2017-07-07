/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:23:40 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/06 15:22:13 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	key_middle_top(t_env *env, int key)
{
	if (key == KEY_L)
	{
		if (env->scene->ambient_light < 0.9)
			env->scene->ambient_light += (0.1 + ACCURACY);
		else
			env->scene->ambient_light = 0.1;
	}
	else if (key == KEY_F)
		use_photo_filter(env);
	else if (key == KEY_Q && env->scene->filter > 0)
		env->scene->filter--;
	else if (key == KEY_E && env->scene->filter < 6)
		env->scene->filter++;
	else
		return (0);
	return (1);
}
