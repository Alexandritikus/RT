/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:38:48 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/03 12:47:15 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fix_scene_list(t_env *env)
{
	t_scene *tmp;

	if (env->scene && ft_strequ(env->scene->title, "maps/cam_only.rt"))
	{
		tmp = env->scene;
		env->scene = env->scene->next;
		if (env->scene)
			env->scene->prev = NULL;
		delete_scene(&tmp, env->mlx);
	}
}

static t_scene	*get_scene(t_scene *list, char *name)
{
	t_scene	*current;

	current = list;
	while (current)
	{
		if (ft_strequ(current->title, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int		choose_scene(t_env *env, char *tytle)
{
	t_scene *active;
	int		redraw;

	redraw = 1;
	fix_scene_list(env);
	if ((active = get_scene(env->scene, tytle)) == NULL)
	{
		if (!(active = parse_scene(tytle, env->mlx, env->sw_image, env->sh)))
			return (0);
		env->scene ? env->scene->prev = active : NULL;
		active->next = env->scene;
		env->scene = active;
		redraw = 2;
	}
	else if (active != env->scene)
	{
		active->prev ? active->prev->next = active->next : NULL;
		active->prev = NULL;
		env->scene->prev = active;
		active->next = env->scene;
		env->scene = active;
	}
	env->mode = MODE_VIEW;
	env->scene->active = NULL;
	return (redraw);
}

static bool		is_in_rectangle(t_vec2 l_u, t_vec2 r_d, t_vec2 place)
{
	if (place.x > l_u.x && place.y > l_u.y)
		if (place.x < r_d.x && place.y < r_d.y)
			return (true);
	return (false);
}

int				check_pic_list(int x, int y, t_env *env)
{
	int			i;
	t_vec_i2	ij;
	const int	x_step = env->sw / 5;
	const int	y_step = env->sh / 3;
	const char	*scene[15] = {SCENE_1, SCENE_2, SCENE_3, SCENE_4, SCENE_5,
							SCENE_6, SCENE_7, SCENE_8, SCENE_9, SCENE_10,
							SCENE_11, SCENE_12, SCENE_13, SCENE_14, SCENE_15};

	i = 0;
	ij.y = 0;
	while (ij.y < env->sh)
	{
		ij.x = 0;
		while (ij.x < env->sw)
		{
			if (is_in_rectangle(vector2(ij.x, ij.y)
				, vector2(ij.x + x_step, ij.y + y_step), vector2(x, y)))
				return (choose_scene(env, (char*)scene[i]));
			ij.x += x_step;
			++i;
		}
		ij.y += y_step;
	}
	return (0);
}
