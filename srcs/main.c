/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:37:33 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 11:38:00 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_res	*get_res_param(char *resolution)
{
	char	*path;
	t_res	*res;

	res = NULL;
	if (ft_strequ(resolution, "hd"))
		path = "images/1280_720/";
	else if (ft_strequ(resolution, "fhd"))
		path = "images/1920_1080/";
	else if (ft_strequ(resolution, "vga"))
		path = "images/640_480/";
	else
		return (res);
	res = (t_res*)malloc(sizeof(t_res));
	res->res = vector2_from_str(path);
	res->title = ft_strjoin(path, TITLE);
	res->pics = ft_strjoin(path, PIC_LIST);
	res->menu = ft_strjoin(path, MENU);
	return (res);
}

static t_env	*initialize_environment(t_res *res)
{
	t_env	*env;
	int		x_tmp;
	int		y_tmp;

	env = (t_env*)malloc(sizeof(t_env));
	env->sw = (int)res->res.x;
	env->sh = (int)res->res.y;
	env->sw_image = (int)res->res.x - SW_MENU;
	env->aspect_ratio = (res->res.x - SW_MENU) / res->res.y;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->sw, env->sh, PROJECT_NAME);
	env->title = mlx_xpm_file_to_image(env->mlx, res->title, &x_tmp, &y_tmp);
	env->pic_list = mlx_xpm_file_to_image(env->mlx, res->pics, &x_tmp, &y_tmp);
	env->menu = mlx_xpm_file_to_image(env->mlx, res->menu, &x_tmp, &y_tmp);
	env->filter = initialize_img(env->mlx, env->sw_image, env->sh);
	env->dublicate_1 = initialize_img(env->mlx, env->sw_image, env->sh);
	env->dublicate_2 = initialize_img(env->mlx, env->sw_image, env->sh);
	env->active = 0;
	env->redraw = 1;
	env->mode = MODE_TITLE;
	env->thread_progress = 0;
	env->scene = NULL;
	return (env);
}

static void		rt(t_env *env)
{
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, exit_x, env);
	mlx_loop(env->mlx);
}

int				main(int argc, char **argv)
{
	t_env	*env;
	t_res	*res_param;

	env = NULL;
	if (argc > 2)
		ft_usage(argv[0]);
	else
	{
		if ((res_param = get_res_param(argc == 1 ? "hd" : argv[1])))
		{
			env = initialize_environment(res_param);
			ft_strdel(&res_param->title);
			ft_strdel(&res_param->pics);
			ft_strdel(&res_param->menu);
			free(res_param);
			rt(env);
		}
		else
			ft_usage(argv[0]);
	}
	return (0);
}
