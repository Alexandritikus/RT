/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 17:37:59 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/15 13:04:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	delete_polygon(t_poly **polygon)
{
	if ((*polygon)->triangle != NULL)
		free((*polygon)->triangle);
	if ((*polygon)->normal != NULL)
		free((*polygon)->normal);
	free(*polygon);
	*polygon = NULL;
}

void		delete_poly_list(t_poly **poly_list)
{
	t_poly	*current;

	current = *poly_list;
	while (current)
	{
		*poly_list = (*poly_list)->next;
		free(current);
		current = *poly_list;
	}
}

void		delete_bsp_tree(t_bsp **tree)
{
	t_bsp	*left;
	t_bsp	*right;

	if (*tree)
	{
		left = (*tree)->left;
		right = (*tree)->right;
		if ((*tree)->depth)
			delete_poly_list(&(*tree)->poly_list);
		free(*tree);
		delete_bsp_tree(&left);
		delete_bsp_tree(&right);
	}
}

void		delete_mesh(t_mesh **mesh)
{
	t_poly	*current;

	if ((*mesh)->polygon)
	{
		current = (*mesh)->polygon;
		while (current)
		{
			(*mesh)->polygon = (*mesh)->polygon->next;
			delete_polygon(&current);
			current = (*mesh)->polygon;
		}
		if ((*mesh)->bsp)
			delete_bsp_tree(&(*mesh)->bsp);
	}
	free(*mesh);
}
