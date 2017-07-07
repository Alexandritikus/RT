/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:03:13 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/23 22:29:42 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

static int		matrix_get_row(t_matrix matrix, int i)
{
	int	k;

	k = i;
	while (k < 4)
	{
		if (matrix.elem[k][i] != 0)
			return (k);
		k++;
	}
	return (-1);
}

static t_matrix	matrix_swap_rows(t_matrix matrix, int i, int j)
{
	t_matrix	result_matrix;
	int			k;
	double		tmp;

	result_matrix = matrix_copy(matrix);
	tmp = 0.0;
	k = -1;
	while (++k < 4)
	{
		tmp = result_matrix.elem[i][k];
		result_matrix.elem[i][k] = result_matrix.elem[j][k];
		result_matrix.elem[j][k] = tmp;
	}
	return (result_matrix);
}

static t_matrix	matrix_div_row(t_matrix matrix, int i, double divisor)
{
	t_matrix	result_matrix;
	int			k;

	result_matrix = matrix_copy(matrix);
	k = -1;
	while (++k < 4)
		result_matrix.elem[i][k] /= divisor;
	return (result_matrix);
}

static void		matrix_sub_row(t_matrix *matrix, t_matrix *result, int i)
{
	double	tmp;
	int		j;
	int		k;

	j = -1;
	while (++j < 4)
	{
		if (j != i)
		{
			tmp = matrix->elem[j][i];
			k = -1;
			while (++k < 4)
			{
				matrix->elem[j][k] -= matrix->elem[i][k] * tmp;
				result->elem[j][k] -= result->elem[i][k] * tmp;
			}
		}
	}
}

t_matrix		matrix_inverse(t_matrix matrix)
{
	int			i;
	int			j;
	t_matrix	result;
	double		tmp;

	result = identity_matrix();
	i = -1;
	while (++i < 4)
	{
		if ((j = matrix_get_row(matrix, i)) != i)
		{
			matrix = matrix_swap_rows(matrix, i, j);
			result = matrix_swap_rows(result, i, j);
		}
		tmp = matrix.elem[i][i];
		matrix = matrix_div_row(matrix, i, tmp);
		result = matrix_div_row(result, i, tmp);
		matrix_sub_row(&matrix, &result, i);
	}
	return (result);
}
