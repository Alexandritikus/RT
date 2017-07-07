/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:12:06 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 16:34:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delete_skybox(t_sky_box **bg, void *mlx)
{
	if ((*bg)->front)
		delete_image(&(*bg)->front, (*bg)->front->img, mlx);
	if ((*bg)->top)
		delete_image(&(*bg)->top, (*bg)->top->img, mlx);
	if ((*bg)->bottom)
		delete_image(&(*bg)->bottom, (*bg)->bottom->img, mlx);
	if ((*bg)->back)
		delete_image(&(*bg)->back, (*bg)->back->img, mlx);
	if ((*bg)->right)
		delete_image(&(*bg)->right, (*bg)->right->img, mlx);
	if ((*bg)->left)
		delete_image(&(*bg)->left, (*bg)->left->img, mlx);
	free(*bg);
	*bg = NULL;
}
