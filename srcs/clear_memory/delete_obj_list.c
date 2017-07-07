/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_obj_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 17:02:07 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:02:31 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	clean_material(t_material *material, void *mlx)
{
	if (material->texture)
		delete_image(&material->texture, material->texture->img, mlx);
	if (material->bump_map)
		delete_image(&material->bump_map, material->bump_map->img, mlx);
}

void		delete_object(t_objs **object, void *mlx)
{
	if ((*object)->obj)
	{
		clean_material(&(*object)->obj->material, mlx);
		if ((*object)->obj->mesh)
			delete_mesh(&(*object)->obj->mesh);
		free((*object)->obj);
	}
	if ((*object)->complex)
		delete_union(&(*object)->complex);
	free(*object);
	*object = NULL;
}

void		delete_obj_list(t_objs **head, void *mlx)
{
	t_objs	*current;

	current = *head;
	while (current)
	{
		*head = (*head)->next;
		delete_object(&current, mlx);
		current = *head;
	}
}
