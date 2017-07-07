/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:11:26 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:12:36 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	intersect_compose(t_ray ray, t_intersect *inter, t_objs *current)
{
	t_ray		tmp_ray;
	t_objs		*union_curr;

	tmp_ray.origin = matrix_to_vector(current->complex->inverse,
														ray.origin, 1);
	tmp_ray.direction = matrix_to_vector(current->complex->inverse,
														ray.direction, 0);
	union_curr = current->complex->obj_list;
	while (union_curr)
	{
		intersect_primitive(tmp_ray, inter, union_curr);
		union_curr = union_curr->next;
	}
}
