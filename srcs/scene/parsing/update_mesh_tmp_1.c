/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mesh_tmp_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 14:28:38 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/09 17:55:38 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void			update_face_list(char *buf, t_face **face_list)
{
	t_face	*list_elem;

	list_elem = (t_face*)malloc(sizeof(t_face));
	list_elem->v1 = vector_from_face(buf, 1);
	list_elem->v2 = vector_from_face(buf, 2);
	list_elem->v3 = vector_from_face(buf, 3);
	list_elem->next = *face_list;
	*face_list = list_elem;
}

static void			update_vert(char *buf, int *n, t_vert **head, t_vert **cur)
{
	t_vert	*list_elem;

	list_elem = (t_vert*)malloc(sizeof(t_vert));
	list_elem->vertex = vector_from_str(buf);
	list_elem->next = *cur;
	list_elem->prev = NULL;
	if (list_elem->next != NULL)
		list_elem->next->prev = list_elem;
	else
		*head = list_elem;
	*cur = list_elem;
	*n += 1;
}

static t_mesh_tmp	*init_mesh_data(void)
{
	t_mesh_tmp	*data;

	data = (t_mesh_tmp*)malloc(sizeof(t_mesh_tmp));
	data->n_vertex = 0;
	data->n_normal = 0;
	data->vertex_head = NULL;
	data->vertex = NULL;
	data->normal_head = NULL;
	data->normal = NULL;
	data->face_list = NULL;
	return (data);
}

void				update_mesh_data(char *buf, t_mesh_tmp **data)
{
	if (*data == NULL)
		*data = init_mesh_data();
	if (buf[0] == 'v' && buf[1] == ' ')
		update_vert(buf, &((*data)->n_vertex),
					&((*data)->vertex_head), &((*data)->vertex));
	else if (buf[0] == 'f' && buf[1] == ' ')
		update_face_list(buf, &((*data)->face_list));
	else if (buf[0] == 'v' && buf[1] == 'n')
		update_vert(buf, &((*data)->n_normal),
					&((*data)->normal_head), &((*data)->normal));
}
