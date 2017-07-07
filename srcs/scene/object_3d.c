/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:52:02 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/15 11:51:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		change_object_matrix(t_object *object)
{
	object->transform = matrix_transform(object->pos,
										object->rot,
										object->scale);
	object->inverse = matrix_inverse(object->transform);
	object->transpose = matrix_transpose(object->inverse);
	if (object->mesh)
	{
		if (object->mesh->bsp)
			delete_bsp_tree(&object->mesh->bsp);
		mesh_update(object);
		object->mesh->bsp = bsp_tree(0, 'x', object->mesh->polygon);
	}
}

t_object	*object_3d(int type, t_orient orient, t_material mat, bool solid)
{
	t_object	*object;

	object = (t_object*)malloc(sizeof(t_object));
	object->type = type;
	object->mode = ROTATE;
	object->color = COLOR_1;
	object->axis = 'x';
	object->solid = solid;
	object->pos = orient.pos;
	object->rot = orient.rot;
	object->scale = vector(MAX(orient.scale.x, ACCURACY),
							MAX(orient.scale.y, ACCURACY),
							MAX(orient.scale.z, ACCURACY));
	object->material = mat;
	object->mesh = NULL;
	change_object_matrix(object);
	object->complex = NULL;
	return (object);
}
