/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 12:26:37 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/02 18:17:49 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

static t_matrix	matrix_rotate(t_vec angle, char axis)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	if (axis == 'x')
	{
		matrix.elem[1][1] = cos(angle.x);
		matrix.elem[2][2] = matrix.elem[1][1];
		matrix.elem[1][2] = -sin(angle.x);
		matrix.elem[2][1] = -matrix.elem[1][2];
	}
	else if (axis == 'y')
	{
		matrix.elem[0][0] = cos(angle.y);
		matrix.elem[2][2] = matrix.elem[0][0];
		matrix.elem[0][2] = sin(angle.y);
		matrix.elem[2][0] = -matrix.elem[0][2];
	}
	else if (axis == 'z')
	{
		matrix.elem[0][0] = cos(angle.z);
		matrix.elem[1][1] = matrix.elem[0][0];
		matrix.elem[0][1] = -sin(angle.z);
		matrix.elem[1][0] = -matrix.elem[0][1];
	}
	return (matrix);
}

static t_matrix	matrix_translate(t_vec vector)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.elem[0][3] = vector.x;
	matrix.elem[1][3] = vector.y;
	matrix.elem[2][3] = vector.z;
	matrix.elem[3][3] = 1;
	return (matrix);
}

static t_matrix	matrix_scale(t_vec vector)
{
	t_matrix	matrix;

	matrix = identity_matrix();
	matrix.elem[0][0] = vector.x;
	matrix.elem[1][1] = vector.y;
	matrix.elem[2][2] = vector.z;
	matrix.elem[3][3] = 1;
	return (matrix);
}

static t_matrix	matrix_mult(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	int			k;
	t_matrix	result_matrix;

	result_matrix = zero_matrix();
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				result_matrix.elem[i][j] += m1.elem[i][k] * m2.elem[k][j];
		}
	}
	return (result_matrix);
}

t_matrix		matrix_transform(t_vec pos, t_vec rot, t_vec scale)
{
	t_matrix	transform_matrix;
	t_matrix	tmp_matrix;

	transform_matrix = identity_matrix();
	tmp_matrix = matrix_translate(pos);
	transform_matrix = matrix_mult(transform_matrix, tmp_matrix);
	if (rot.x != 0)
	{
		tmp_matrix = matrix_rotate(rot, 'x');
		transform_matrix = matrix_mult(transform_matrix, tmp_matrix);
	}
	if (rot.y != 0)
	{
		tmp_matrix = matrix_rotate(rot, 'y');
		transform_matrix = matrix_mult(transform_matrix, tmp_matrix);
	}
	if (rot.z != 0)
	{
		tmp_matrix = matrix_rotate(rot, 'z');
		transform_matrix = matrix_mult(transform_matrix, tmp_matrix);
	}
	tmp_matrix = matrix_scale(scale);
	transform_matrix = matrix_mult(transform_matrix, tmp_matrix);
	return (transform_matrix);
}
