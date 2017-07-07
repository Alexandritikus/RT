/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:30:46 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 12:30:48 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

static t_vec	vector_rotate_x(t_vec vec, double a)
{
	double	y;
	double	z;
	t_vec	rotated;

	y = vec.y;
	z = vec.z;
	rotated.x = vec.x;
	rotated.y = y * cos(a) - z * sin(a);
	rotated.z = y * sin(a) + z * cos(a);
	return (rotated);
}

static t_vec	vector_rotate_y(t_vec vec, double a)
{
	double	x;
	double	z;
	t_vec	rotated;

	x = vec.x;
	z = vec.z;
	rotated.x = x * cos(a) + z * sin(a);
	rotated.y = vec.y;
	rotated.z = z * cos(a) - x * sin(a);
	return (rotated);
}

static t_vec	vector_rotate_z(t_vec vec, double a)
{
	double	x;
	double	y;
	t_vec	rotated;

	x = vec.x;
	y = vec.y;
	rotated.x = x * cos(a) - y * sin(a);
	rotated.y = x * sin(a) + y * cos(a);
	rotated.z = vec.z;
	return (rotated);
}

t_vec			vector_rotate(t_vec vec, t_vec rotate)
{
	t_vec	rotated;

	rotated = vec;
	if (rotate.x > ACCURACY || rotate.x < -ACCURACY)
		rotated = vector_rotate_x(rotated, rotate.x);
	if (rotate.y > ACCURACY || rotate.y < -ACCURACY)
		rotated = vector_rotate_y(rotated, rotate.y);
	if (rotate.z > ACCURACY || rotated.z < -ACCURACY)
		rotated = vector_rotate_z(rotated, rotate.z);
	return (rotated);
}
