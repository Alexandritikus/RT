/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_obj_tmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:16:03 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/06 13:04:47 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void		delete_vertex_list(t_vert *list)
{
	t_vert	*current;

	current = list;
	while (current)
	{
		list = list->next;
		free(current);
		current = list;
	}
}

static void		delete_mesh_data(t_mesh_tmp **data)
{
	t_face	*current_face;

	if (*data)
	{
		current_face = (*data)->face_list;
		while (current_face)
		{
			(*data)->face_list = (*data)->face_list->next;
			free(current_face);
			current_face = (*data)->face_list;
		}
		delete_vertex_list((*data)->vertex);
		delete_vertex_list((*data)->normal);
		free(*data);
	}
}

static t_mesh	*read_mesh(char *obj_file)
{
	int			fd;
	char		*buf;
	t_mesh_tmp	*mesh_data;
	t_mesh		*mesh;

	buf = NULL;
	mesh_data = NULL;
	mesh = NULL;
	if ((fd = open(obj_file, O_RDONLY)) > 2)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			if (buf && *buf != '#')
				update_mesh_data(buf, &mesh_data);
			ft_strdel(&buf);
		}
	}
	close(fd);
	if (mesh_data && mesh_data->vertex && mesh_data->face_list)
		mesh = create_mesh(mesh_data);
	delete_mesh_data(&mesh_data);
	free(obj_file);
	return (mesh);
}

void			update_obj_tmp(t_obj_tmp **data, char *buf, void *mlx, int type)
{
	if (type != (int)MESH && ft_strstr(buf, "solid"))
		(*data)->solid = (ft_strstr(buf, "true") ? true : false);
	else if (type == (int)MESH &&
		ft_strstr(buf, "link") && (*data)->mesh_link == NULL)
	{
		if (((*data)->mesh_link = ft_link_from_str(buf)) != NULL)
			(*data)->mesh = read_mesh((*data)->mesh_link);
	}
	else if (ft_strstr(buf, "position"))
		(*data)->orientation.pos = vector_from_str(buf);
	else if (ft_strstr(buf, "rotation"))
		(*data)->orientation.rot = vector_mult_d(vector_from_str(buf),
													RAD_COEF);
	else if (ft_strstr(buf, "object_scale"))
		(*data)->orientation.scale = vector_from_str(buf);
	else if (type == (int)TORUS && ft_strstr(buf, "inner_radius:"))
		(*data)->torus_in_radius = MIN(1.0, MAX(0.0,
										ft_atof(ft_strchr(buf, ':') + 1)));
	else
		update_material(&(*data)->material, buf, mlx);
}
