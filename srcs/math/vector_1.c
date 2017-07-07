/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:17:31 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/16 12:02:29 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_vec	vector(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec	vector_zero(void)
{
	return (vector(0, 0, 0));
}

t_vec	vector_one(double coord)
{
	return (vector(coord, coord, coord));
}

t_vec	vector_div_d(t_vec vec, double d)
{
	return (vector(vec.x / d, vec.y / d, vec.z / d));
}

t_vec	vector_mult_d(t_vec vec, double m)
{
	return (vector(vec.x * m, vec.y * m, vec.z * m));
}
