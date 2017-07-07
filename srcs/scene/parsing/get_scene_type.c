/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:41:49 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/09 18:05:44 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static int	base_env(const char *buf)
{
	int	type;

	type = -1;
	if (ft_strstr(buf, "scene"))
		type = SCENE;
	else if (ft_strstr(buf, "light"))
		type = LIGHT;
	return (type);
}

static int	base_limited(const char *buf)
{
	int	type;

	type = -1;
	if (ft_strstr(buf, "sphere"))
		type = SPHERE;
	else if (ft_strstr(buf, "cylinder"))
		type = CYLINDER;
	else if (ft_strstr(buf, "cone"))
		type = CONE;
	else if (ft_strstr(buf, "triangle"))
		type = TRIANGLE;
	else if (ft_strstr(buf, "plane"))
		type = PLANE;
	else if (ft_strstr(buf, "disc"))
		type = DISC;
	else if (ft_strstr(buf, "cube"))
		type = CUBE;
	else if (ft_strstr(buf, "tube"))
		type = TUBE;
	else if (ft_strstr(buf, "capsule"))
		type = CAPSULE;
	else if (ft_strstr(buf, "paraboloid"))
		type = PARABOLOID;
	return (type);
}

static int	addition_limited(const char *buf)
{
	int	type;

	type = -1;
	if (ft_strstr(buf, "torus"))
		type = TORUS;
	else if (ft_strstr(buf, "moebius"))
		type = MOEBIUS;
	return (type);
}

int			get_scene_type(const char *buf, int prev_type)
{
	int	current_type;

	current_type = 0;
	if (*buf == '#' && prev_type == -1)
	{
		if ((current_type = base_env(buf)) >= 0)
			return (current_type);
		else if ((current_type = base_limited(buf)) >= 0)
			return (current_type);
		else if ((current_type = addition_limited(buf)) >= 0)
			return (current_type);
		else if (ft_strstr(buf, "mesh"))
			return (MESH);
		else if (ft_strstr(buf, "union"))
			return (UNION);
	}
	return (prev_type);
}
