/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:57:32 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 19:59:25 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

void		calculate_view(t_camera *cam)
{
	t_vec	n;
	t_vec	u;
	t_vec	v;

	n = vector_normalize(vector_sub(cam->position, cam->look_at));
	n = vector_rotate(n, cam->rotation);
	u = vector_normalize(vector_cross(cam->up, n));
	v = vector_cross(n, u);
	cam->view.elem[0][0] = u.x;
	cam->view.elem[0][1] = u.y;
	cam->view.elem[0][2] = u.z;
	cam->view.elem[0][3] = -vector_dot(u, cam->position);
	cam->view.elem[1][0] = v.x;
	cam->view.elem[1][1] = v.y;
	cam->view.elem[1][2] = v.z;
	cam->view.elem[1][3] = -vector_dot(v, cam->position);
	cam->view.elem[2][0] = n.x;
	cam->view.elem[2][1] = n.y;
	cam->view.elem[2][2] = n.z;
	cam->view.elem[2][3] = -vector_dot(n, cam->position);
	cam->view.elem[3][0] = 0;
	cam->view.elem[3][1] = 0;
	cam->view.elem[3][2] = 0;
	cam->view.elem[3][3] = 1;
}

t_camera	*camera(t_vec pos, t_vec look_at, t_vec rotation)
{
	t_camera	*cam;

	cam = (t_camera*)malloc(sizeof(t_camera));
	cam->position = pos;
	cam->look_at = look_at;
	cam->rotation = rotation;
	cam->up = vector(0, 1, 0);
	calculate_view(cam);
	return (cam);
}
