/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_from_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:24:59 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 18:23:06 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define FRONT	"front.xpm"
#define TOP		"top.xpm"
#define BOTTOM	"bottom.xpm"
#define BACK	"back.xpm"
#define RIGHT	"right.xpm"
#define LEFT	"left.xpm"

static t_img	*img_for_sky_box(char *path, char *title, void *mlx)
{
	char	*link;
	int		access_right;
	t_img	*img;

	link = ft_strjoin(path, title);
	img = NULL;
	if ((access_right = access(link, F_OK)) == 0)
		img = img_from_xpm(link, mlx);
	ft_strdel(&link);
	return (img);
}

t_sky_box		*get_sky_box(char *link, void *mlx)
{
	t_sky_box	*bg;

	bg = (t_sky_box*)malloc(sizeof(t_sky_box));
	bg->front = NULL;
	bg->top = NULL;
	bg->bottom = NULL;
	bg->back = NULL;
	bg->right = NULL;
	bg->left = NULL;
	if ((bg->front = img_for_sky_box(link, FRONT, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	else if ((bg->top = img_for_sky_box(link, TOP, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	else if ((bg->bottom = img_for_sky_box(link, BOTTOM, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	else if ((bg->back = img_for_sky_box(link, BACK, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	else if ((bg->right = img_for_sky_box(link, RIGHT, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	else if ((bg->left = img_for_sky_box(link, LEFT, mlx)) == NULL)
		delete_skybox(&bg, mlx);
	return (bg);
}

t_img			*img_from_xpm(char *file_name, void *mlx)
{
	t_img	*texture;

	texture = (t_img*)malloc(sizeof(t_img));
	texture->img = mlx_xpm_file_to_image(mlx, file_name,
											&texture->width, &texture->height);
	texture->adr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
									&texture->size_line, &texture->endian);
	return (texture);
}

t_img			*texture_from_file(char *buf, void *mlx)
{
	char	*file_name;
	int		access_right;
	t_img	*texture;

	texture = NULL;
	if ((file_name = ft_link_from_str(buf)) != NULL)
	{
		if ((access_right = access(file_name, F_OK)) == 0)
			texture = img_from_xpm(file_name, mlx);
		free(file_name);
	}
	return (texture);
}
