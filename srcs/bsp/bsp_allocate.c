/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_allocate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:39:02 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:01:42 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static void	ini_min_max(char axis, t_boundaries curr, double *min, double *max)
{
	if (axis == 'x')
	{
		*min = curr.min.x;
		*max = curr.max.x;
	}
	else if (axis == 'y')
	{
		*min = curr.min.y;
		*max = curr.max.y;
	}
	else
	{
		*min = curr.min.z;
		*max = curr.max.z;
	}
}

static void	calculate_new_branch(t_poly *tmp, t_poly **branch)
{
	while (*branch)
		branch = &(*branch)->next;
	*branch = (t_poly*)malloc(sizeof(t_poly));
	(*branch)->triangle = tmp->triangle;
	(*branch)->normal = tmp->normal;
	(*branch)->bounds = tmp->bounds;
	(*branch)->next = NULL;
}

void		bsp_alloc(t_bsp *bspp, t_poly **l, t_poly **r)
{
	double	split;
	t_poly	*tmp;
	t_vec	min_max;

	*l = NULL;
	*r = NULL;
	tmp = bspp->poly_list;
	split = split_value(bspp->bounds, bspp->axis);
	while (tmp)
	{
		ini_min_max(bspp->axis, tmp->bounds, &min_max.x, &min_max.y);
		if (min_max.x < split)
			calculate_new_branch(tmp, l);
		if (min_max.y >= split)
			calculate_new_branch(tmp, r);
		tmp = tmp->next;
	}
}
