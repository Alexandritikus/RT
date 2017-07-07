/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_creative_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:45:09 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 11:26:20 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define START_LINE "---CREATIVE MODE(Fn + F4)---"

static char	*active_mode(int mode)
{
	if (mode == ROTATE)
		return ("ROTATE");
	else if (mode == TRANSLATE)
		return ("TRANSLATE");
	else
		return ("SCALE");
}

static char	*which_material(int type)
{
	if (type == CHECKBOARD)
		return ("CHECKBOARD");
	if (type == CRISSCROSS)
		return ("CRISSCROSS");
	if (type == MARBLE)
		return ("MARBLE");
	if (type == SHINYCOLOR)
		return ("SHINYCOLOR");
	if (type == TURBULENCE)
		return ("TURBULENCE");
	if (type == WOOD)
		return ("WOOD");
	if (type == FLATCOLOR)
		return ("FLATCOLOR");
	else
		return ("GLASS");
}

static char	*active_color(int color)
{
	if (color == COLOR_1)
		return ("COLOR_1");
	else if (color == COLOR_2)
		return ("COLOR_2");
	else
		return ("COLOR_3");
}

static void	print_material(void *mlx, void *win, int start, t_env *env)
{
	char	*tmp;

	mlx_string_put(mlx, win, start + 10, 370, BLACK, "Active color (4/6):");
	mlx_string_put(mlx, win, start + 210, 370, BLACK,
								active_color(env->scene->active->color));
	mlx_string_put(mlx, win, start + 70, 390, BLACK, "R: 7/1 | to change");
	mlx_string_put(mlx, win, start + 70, 410, BLACK, "G: 8/2 | to change");
	mlx_string_put(mlx, win, start + 70, 430, BLACK, "B: 9/3 | to change");
	mlx_string_put(mlx, win, start + 10, 450, BLACK, "Scale (9/0):");
	tmp = ft_itoa(env->scene->active->material.scale * 10);
	mlx_string_put(mlx, win, start + 250, 450, BLACK, tmp);
	ft_strdel(&tmp);
	mlx_string_put(mlx, win, start + 10, 470, BLACK, "Material ({/}):");
	mlx_string_put(mlx, win, start + 190, 470, BLACK,
							which_material(env->scene->active->material.type));
	mlx_string_put(mlx, win, start + 10, 490, BLACK, "Delete object (DEL)");
}

void		print_creative_mode(void *mlx, void *win, int start, t_env *env)
{
	int	color;

	color = (env->mode == MODE_CREATE ? GREEN : BLACK);
	mlx_string_put(mlx, win, start + 10, 310, color, START_LINE);
	if (env->scene->active)
	{
		mlx_string_put(mlx, win, start + 10, 330, BLACK, "Active axis (</>):");
		mlx_string_put(mlx, win, start + 250, 330, BLACK,
			env->scene->active->complex ? &env->scene->active->complex->axis :
													&env->scene->active->axis);
		mlx_string_put(mlx, win, start + 10, 350, BLACK, "Active mode (N/M):");
		mlx_string_put(mlx, win, start + 200, 350, BLACK,
			active_mode(env->scene->active->complex ?
				env->scene->active->complex->mode : env->scene->active->mode));
		print_material(mlx, win, start, env);
	}
	mlx_string_put(mlx, win, start + 70, 510, color, "CREATE NEW OBJECT:");
	mlx_string_put(mlx, win, start + 10, 530, BLACK, "I - CYLINDER");
	mlx_string_put(mlx, win, start + 150, 530, BLACK, "O - SPHERE");
	mlx_string_put(mlx, win, start + 10, 550, BLACK, "P - PLANE");
	mlx_string_put(mlx, win, start + 150, 550, BLACK, "C - CONE");
}
