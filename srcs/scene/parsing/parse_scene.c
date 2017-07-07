/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 14:43:03 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 16:39:36 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img			*initialize_img(void *mlx, int width, int height)
{
	t_img	*pic;

	pic = (t_img*)malloc(sizeof(t_img));
	pic->img = mlx_new_image(mlx, width, height);
	pic->adr = mlx_get_data_addr(pic->img, &pic->bits_per_pixel,
		&pic->size_line, &pic->endian);
	pic->width = width;
	pic->height = height;
	return (pic);
}

static t_scene	*initialize_scene(char *title, void *mlx, int sw, int sh)
{
	t_scene	*scene;

	scene = (t_scene*)malloc(sizeof(t_scene));
	scene->title = title;
	scene->pic = initialize_img(mlx, sw, sh);
	scene->camera = NULL;
	scene->obj_list = NULL;
	scene->active = NULL;
	scene->light = NULL;
	scene->bg = NULL;
	scene->bg_color = color_zero();
	scene->effects = true;
	scene->antialias = false;
	scene->ssaa = 1;
	scene->max_reflections = 1;
	scene->shadow_samples = 1;
	scene->lvl = 1;
	scene->m_blur_k = 1;
	scene->filter = NONE;
	scene->ambient_light = 0.2;
	scene->next = NULL;
	scene->prev = NULL;
	return (scene);
}

static void		update_scene_obj(t_scene_obj **obj, char *buf, int t, void *mlx)
{
	if (*obj == NULL)
		*obj = create_scene_object(t);
	if (*buf == '}')
		(*obj)->status = true;
	else if (t == 0 && (*obj)->scene_data)
		update_scene_tmp(&(*obj)->scene_data, buf, mlx);
	else if (t > 0 && t < 100 && (*obj)->obj_data)
		update_obj_tmp(&(*obj)->obj_data, buf, mlx, t);
	else if (t == (int)LIGHT && (*obj)->light_data)
		update_light_tmp(&(*obj)->light_data, buf);
	else if (t == (int)UNION && (*obj)->union_data)
		update_union_tmp(&(*obj)->union_data, buf);
}

t_scene			*parse_scene(char *file_name, void *mlx, int sw, int sh)
{
	t_scene		*scene;
	t_scene_obj	*scene_object;
	int			scene_type;
	int			fd;
	char		*buf;

	scene = initialize_scene(file_name, mlx, sw, sh);
	scene_object = NULL;
	scene_type = -1;
	buf = NULL;
	if ((fd = open(file_name, O_RDONLY)) > 2)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			if (buf && (scene_type = get_scene_type(buf, scene_type)) != -1)
				update_scene_obj(&scene_object, buf, scene_type, mlx);
			if (scene_object && scene_object->status)
				update_scene(&scene_object, &scene, &scene_type);
			ft_strdel(&buf);
		}
	}
	close(fd);
	if (scene && !scene->camera)
		delete_scene(&scene, mlx);
	return (scene);
}
