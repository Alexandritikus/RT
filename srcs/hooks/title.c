/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:56:17 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 12:49:56 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	new_scene(t_env **env)
{
	t_scene	*new_scene;

	fix_scene_list(*env);
	if ((*env)->scene == NULL)
		(*env)->scene = parse_scene("maps/cam_only.rt", (*env)->mlx,
												(*env)->sw_image, (*env)->sh);
	else
	{
		new_scene = parse_scene("maps/cam_only.rt", (*env)->mlx,
												(*env)->sw_image, (*env)->sh);
		new_scene->prev = NULL;
		new_scene->next = (*env)->scene;
		(*env)->scene = new_scene;
	}
}

int			check_title(int x, int y, t_env *env)
{
	int	redraw;
	int	button_u[4];
	int	button_dy[2];

	button_u[0] = env->sw - (env->sw * 0.4) - 5;
	button_u[1] = 5;
	button_u[2] = env->sw - 5;
	button_u[3] = 5 + (env->sh * 0.4);
	button_dy[0] = env->sh - 5 - (env->sh * 0.4);
	button_dy[1] = env->sh - 5;
	redraw = 0;
	if (x >= button_u[0] && x <= button_u[2]
		&& y >= button_u[1] && y <= button_u[3])
	{
		env->mode = MODE_PIC_LIST;
		redraw = 1;
	}
	else if (x >= button_u[0] && x <= button_u[2]
		&& y >= button_dy[0] && y <= button_dy[1])
	{
		env->mode = MODE_CREATE;
		new_scene(&env);
		redraw = 2;
	}
	return (redraw);
}
