/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_union.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 17:29:16 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 17:34:59 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delete_union(t_union **complex)
{
	t_objs	*current;

	current = (*complex)->obj_list;
	while (current)
	{
		(*complex)->obj_list = (*complex)->obj_list->next;
		free(current);
		current = (*complex)->obj_list;
	}
	free(*complex);
	*complex = NULL;
}
