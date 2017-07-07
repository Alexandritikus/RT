/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mesh_tmp_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:22:59 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:05:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"
#include <stdio.h>

static double	get_mesh_radius(t_vert *vert_list)
{
	t_vert	*current;
	double	max;
	double	x_tmp;
	double	y_tmp;
	double	z_tmp;

	current = vert_list;
	max = 0.0;
	while (current)
	{
		x_tmp = ABS(current->vertex.x);
		y_tmp = ABS(current->vertex.y);
		z_tmp = ABS(current->vertex.z);
		if (x_tmp > max)
			max = x_tmp;
		if (y_tmp > max)
			max = y_tmp;
		if (z_tmp > max)
			max = z_tmp;
		current = current->next;
	}
	return (max);
}

static t_vec	*vec_array_from_list(t_vert *head, int num)
{
	t_vec	*array;
	int		i;
	t_vert	*current;

	array = (t_vec*)malloc(sizeof(t_vec) * num);
	current = head;
	i = -1;
	while (++i < num)
	{
		array[i] = current->vertex;
		current = current->prev;
	}
	return (array);
}

static t_tri	*fill_poly_elem(t_vec *array, t_face *current, int max, char c)
{
	t_tri	*tri;

	tri = NULL;
	if (array == NULL)
		return (NULL);
	else if (c == 'x')
		tri = triangle(array[MIN((int)current->v1.x - 1, max)],
							array[MIN((int)current->v2.x - 1, max)],
							array[MIN((int)current->v3.x - 1, max)]);
	else if (c == 'y')
		tri = triangle(array[MIN((int)current->v1.y - 1, max)],
							array[MIN((int)current->v2.y - 1, max)],
							array[MIN((int)current->v3.y - 1, max)]);
	else if (c == 'z')
		tri = triangle(array[MIN((int)current->v1.z - 1, max)],
							array[MIN((int)current->v2.z - 1, max)],
							array[MIN((int)current->v3.z - 1, max)]);
	return (tri);
}

static t_poly	*mesh_polygon(t_mesh_tmp *data)
{
	t_poly	*poly;
	t_poly	*elem;
	t_vec	*vertex_array;
	t_vec	*normal_array;
	t_face	*cur;

	poly = NULL;
	normal_array = (data->normal_head == 0 ? NULL :
					vec_array_from_list(data->normal_head, data->n_normal));
	vertex_array = vec_array_from_list(data->vertex_head, data->n_vertex);
	cur = data->face_list;
	while (cur)
	{
		elem = (t_poly*)malloc(sizeof(t_poly));
		elem->triangle = fill_poly_elem(vertex_array, cur, data->n_vertex, 'x');
		elem->normal = fill_poly_elem(normal_array, cur, data->n_normal, 'z');
		elem->next = poly;
		poly = elem;
		cur = cur->next;
	}
	free(vertex_array);
	if (normal_array)
		free(normal_array);
	return (poly);
}

t_mesh			*create_mesh(t_mesh_tmp *data)
{
	t_mesh	*mesh;

	mesh = (t_mesh*)malloc(sizeof(t_mesh));
	mesh->face_type = (data->n_normal == 0 ? V_ONLY : V_NORM);
	mesh->polygon = mesh_polygon(data);
	mesh->radius = get_mesh_radius(data->vertex);
	mesh->bsp = NULL;
	return (mesh);
}
