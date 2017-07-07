/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 15:44:04 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 12:17:39 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	delete_light(t_light **light)
{
	t_light	*current;

	current = *light;
	while (current)
	{
		*light = (*light)->next;
		free(current);
		current = *light;
	}
}

void		delete_scene(t_scene **scene, void *mlx)
{
	delete_image(&(*scene)->pic, (*scene)->pic->img, mlx);
	if ((*scene)->bg)
		delete_skybox(&(*scene)->bg, mlx);
	if ((*scene)->light)
		delete_light(&(*scene)->light);
	if ((*scene)->camera)
		free((*scene)->camera);
	if ((*scene)->obj_list)
		delete_obj_list(&(*scene)->obj_list, mlx);
	free(*scene);
	*scene = NULL;
}
