/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:26:38 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/16 12:02:32 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_vec	vector_div_vec(t_vec v1, t_vec v2)
{
	return (vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z));
}

t_vec	vector_mult_vec(t_vec v1, t_vec v2)
{
	return (vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vec	vector_add(t_vec v1, t_vec v2)
{
	return (vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	vector_sub(t_vec v1, t_vec v2)
{
	return (vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

double	vector_length(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
