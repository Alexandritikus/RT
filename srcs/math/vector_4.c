/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiholkin <aiholkin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:54:05 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/09 17:22:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

t_vec	vector_negative(t_vec vector)
{
	t_vec	negative;

	negative.x = -vector.x;
	negative.y = -vector.y;
	negative.z = -vector.z;
	return (negative);
}

double	dist_to_dot(t_vec p1, t_vec p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) +
				(p1.y - p2.y) * (p1.y - p2.y) +
				(p1.z - p2.z) * (p1.z - p2.z)));
}

t_vec2	vector2_zero(void)
{
	t_vec2	vec;

	vec.x = 0;
	vec.y = 0;
	return (vec);
}

t_vec2	vector2(double x, double y)
{
	t_vec2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}
