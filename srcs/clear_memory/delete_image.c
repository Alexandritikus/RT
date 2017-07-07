/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:22:26 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 18:30:01 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delete_image(t_img **img, void *img_ptr, void *mlx)
{
	if (img_ptr)
		mlx_destroy_image(mlx, img_ptr);
	free(*img);
	*img = NULL;
}
