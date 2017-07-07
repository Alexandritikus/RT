/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:38:04 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/16 12:02:34 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

double	vector_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vector_cross(t_vec v1, t_vec v2)
{
	return (vector(v1.y * v2.z - v2.y * v1.z,
					v2.x * v1.z - v1.x * v2.z,
					v1.x * v2.y - v2.x * v1.y));
}

t_vec	vector_normalize(t_vec vec)
{
	double len;

	len = vector_length(vec);
	if (len != 0)
		return (vector(vec.x / len, vec.y / len, vec.z / len));
	else
		return (vec);
}

double	vector_length2(t_vec vec)
{
	return (vector_dot(vec, vec));
}

t_vec	vector_project(t_vec v1, t_vec v2)
{
	return (vector_mult_d(v2, (vector_dot(v1, v2) / vector_length2(v2))));
}
