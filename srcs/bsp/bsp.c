/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:33:14 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 21:09:53 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define MIN_OBJECT_COUNT 100

int		count_obj(t_poly *poly)
{
	int		count;
	t_poly	*current;

	count = 0;
	current = poly;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_bsp	*bsp_tree(int depth, char axis, t_poly *objects)
{
	t_bsp	*ret;

	ret = (t_bsp*)malloc(sizeof(t_bsp));
	ret->depth = depth;
	ret->axis = axis;
	ret->poly_list = objects;
	ret->axis_retries = 0;
	ret->bounds = boundaries();
	ret->left = NULL;
	ret->right = NULL;
	build(ret);
	return (ret);
}

void	count_bounds(t_bsp *bspp)
{
	t_poly			*current;
	t_boundaries	curr;

	current = bspp->poly_list;
	while (current)
	{
		curr = current->bounds;
		bspp->bounds.min = vector(MIN(bspp->bounds.min.x, curr.min.x),
									MIN(bspp->bounds.min.y, curr.min.y),
									MIN(bspp->bounds.min.z, curr.min.z));
		bspp->bounds.max = vector(MAX(bspp->bounds.max.x, curr.max.x),
									MAX(bspp->bounds.max.y, curr.max.y),
									MAX(bspp->bounds.max.z, curr.max.z));
		current = current->next;
	}
}

char	toggle_axis(t_bsp *bsp)
{
	if (bsp->axis == 'x')
		return ('y');
	else if (bsp->axis == 'y')
		return ('z');
	else
		return ('x');
}

void	build(t_bsp *bspp)
{
	t_poly	*left_objects;
	t_poly	*right_objects;
	char	new_axis;

	count_bounds(bspp);
	if (count_obj(bspp->poly_list) <= MIN_OBJECT_COUNT)
		return ;
	bsp_alloc(bspp, &left_objects, &right_objects);
	new_axis = toggle_axis(bspp);
	if (count_obj(bspp->poly_list) > count_obj(left_objects) &&
		count_obj(bspp->poly_list) > count_obj(right_objects))
	{
		bspp->left = bsp_tree(bspp->depth + 1, new_axis, left_objects);
		bspp->right = bsp_tree(bspp->depth + 1, new_axis, right_objects);
	}
	else
	{
		delete_poly_list(&left_objects);
		delete_poly_list(&right_objects);
		if (bspp->axis_retries >= 2)
			return ;
		bspp->axis = toggle_axis(bspp);
		bspp->axis_retries++;
		build(bspp);
	}
}
