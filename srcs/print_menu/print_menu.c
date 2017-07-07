/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 14:34:29 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/22 11:24:51 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define START_LINE "---------- CAMERA ----------"
#define LINE "----------------------------"

static char	*which_photo_filter(int filter)
{
	if (filter == GREYSCALE)
		return ("GREYSCALE");
	else if (filter == B_W)
		return ("BLCK_&_WHT");
	else if (filter == NEGATIVE)
		return ("NEGATIVE");
	else if (filter == SEPIA)
		return ("SEPIA");
	else if (filter == WARM)
		return ("WARM");
	else if (filter == MOTION_BLUR)
		return ("M_BLUR");
	else
		return ("NOT DEFINED");
}

static void	print_up_top(void *mlx, void *win, int x_start, t_env *env)
{
	int		color[2];
	char	*tmp;

	color[0] = (env->scene->effects ? GREEN : RED);
	color[1] = (env->scene->antialias ? GREEN : RED);
	mlx_string_put(mlx, win, x_start + 10, 70, BLACK, "Redraw (R)");
	mlx_string_put(mlx, win, x_start + 10, 90, BLACK, "Effects (Fn + F2):");
	mlx_string_put(mlx, win, x_start + 250, 90, color[0],
										env->scene->effects ? "ON" : "OFF");
	mlx_string_put(mlx, win, x_start + 10, 110, BLACK, "Antialias (Fn + F1):");
	mlx_string_put(mlx, win, x_start + 250, 110, color[1],
										env->scene->antialias ? "ON" : "OFF");
	mlx_string_put(mlx, win, x_start + 10, 130, BLACK, "SSAA level (PAD +/-):");
	tmp = ft_itoa(env->scene->ssaa);
	mlx_string_put(mlx, win, x_start + 250, 130, BLACK, tmp);
	ft_strdel(&tmp);
	mlx_string_put(mlx, win, x_start + 10, 150, BLACK, "Motion blur (B):");
	tmp = ft_itoa(env->scene->m_blur_k);
	mlx_string_put(mlx, win, x_start + 250, 150, BLACK, tmp);
	ft_strdel(&tmp);
}

static void	print_mid_top(void *mlx, void *win, int x_start, t_env *env)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(env->scene->ambient_light * 10.0);
	tmp2 = ft_strjoin("0.", tmp1);
	ft_strdel(&tmp1);
	mlx_string_put(mlx, win, x_start + 10, 170, BLACK, "Ambientlight (L):");
	mlx_string_put(mlx, win, x_start + 250, 170, BLACK, tmp2);
	ft_strdel(&tmp2);
	mlx_string_put(mlx, win, x_start + 10, 190, BLACK, "Photo filter (F):");
	mlx_string_put(mlx, win, x_start + 180, 190, BLACK,
										which_photo_filter(env->scene->filter));
	mlx_string_put(mlx, win, x_start + 70, 210, BLACK, "Q / E to change type");
}

static void	print_camera(void *mlx, void *win, int x_start, t_env *env)
{
	char	*tmp;

	mlx_string_put(mlx, win, x_start + 10, 230, BLACK, START_LINE);
	mlx_string_put(mlx, win, x_start + 10, 250, BLACK, "W S A D - + to move");
	mlx_string_put(mlx, win, x_start + 10, 270, BLACK, "< > ^ v to rotate");
	mlx_string_put(mlx, win, x_start + 10, 290, BLACK, "move coef (Z / X):");
	tmp = ft_itoa(env->scene->lvl);
	mlx_string_put(mlx, win, x_start + 250, 290, BLACK, tmp);
	ft_strdel(&tmp);
}

void		print_menu(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->menu, env->sw_image, 0);
	print_up_top(env->mlx, env->win, env->sw_image, env);
	print_mid_top(env->mlx, env->win, env->sw_image, env);
	print_camera(env->mlx, env->win, env->sw_image, env);
	print_creative_mode(env->mlx, env->win, env->sw_image, env);
	mlx_string_put(env->mlx, env->win, env->sw_image + 10, 670, BLACK, LINE);
	mlx_string_put(env->mlx, env->win, env->sw_image + 10, 690, BLACK,
													"Save to .bmp (Fn + F3)");
}
