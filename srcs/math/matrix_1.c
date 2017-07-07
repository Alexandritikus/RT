/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:28:53 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 22:30:02 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_matrix	zero_matrix(void)
{
	t_matrix	matrix;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			matrix.elem[i][j] = 0;
	}
	return (matrix);
}

t_matrix	identity_matrix(void)
{
	t_matrix	matrix;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			matrix.elem[i][j] = (i == j ? 1 : 0);
	}
	return (matrix);
}

t_matrix	matrix_from_vector(double *vector)
{
	t_matrix	matrix;
	int			i;

	matrix = zero_matrix();
	i = -1;
	while (++i < 16)
		matrix.elem[i / 4][i % 4] = vector[i];
	return (matrix);
}

t_matrix	matrix_copy(t_matrix matrix)
{
	t_matrix	new_matrix;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			new_matrix.elem[i][j] = matrix.elem[i][j];
	}
	return (new_matrix);
}

t_matrix	matrix_transpose(t_matrix matrix)
{
	int			i;
	int			j;
	t_matrix	result_matrix;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			result_matrix.elem[i][j] = matrix.elem[j][i];
	}
	return (result_matrix);
}
