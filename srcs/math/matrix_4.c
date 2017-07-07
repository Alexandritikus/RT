/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:59:28 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/02 16:46:08 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_vec		matrix_to_vector(t_matrix matrix, t_vec point, int toggle)
{
	t_vec	result;

	result.x = vector_dot(point, vector(matrix.elem[0][0],
										matrix.elem[0][1],
										matrix.elem[0][2])) +
										matrix.elem[0][3] * toggle;
	result.y = vector_dot(point, vector(matrix.elem[1][0],
										matrix.elem[1][1],
										matrix.elem[1][2])) +
										matrix.elem[1][3] * toggle;
	result.z = vector_dot(point, vector(matrix.elem[2][0],
										matrix.elem[2][1],
										matrix.elem[2][2])) +
										matrix.elem[2][3] * toggle;
	return (result);
}

t_matrix	disc_rotate(double angle, t_vec vec)
{
	t_matrix	matrix;
	double		c;
	double		s;
	double		oc;

	matrix = identity_matrix();
	angle = angle * RAD_COEF;
	c = cos(angle);
	s = sin(angle);
	oc = 1.0 - c;
	matrix.elem[0][0] = vec.x * vec.x * oc + c;
	matrix.elem[1][0] = vec.x * vec.y * oc + vec.z * s;
	matrix.elem[2][0] = vec.x * vec.z * oc - vec.y * s;
	matrix.elem[0][1] = vec.x * vec.y * oc - vec.z * s;
	matrix.elem[1][1] = vec.y * vec.y * oc + c;
	matrix.elem[2][1] = vec.y * vec.z * oc + vec.x * s;
	matrix.elem[0][2] = vec.x * vec.z * oc + vec.y * s;
	matrix.elem[1][2] = vec.y * vec.z * oc - vec.x * s;
	matrix.elem[2][2] = vec.z * vec.z * oc + c;
	return (matrix);
}
