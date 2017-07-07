/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:41:30 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/05 12:59:53 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object	*find_objs(t_objs *obj_list, int i)
{
	int		j;
	t_objs	*tmp;

	j = 1;
	tmp = obj_list;
	if (i <= 0)
		return (NULL);
	while (tmp)
	{
		if (i == j++)
		{
			if ((tmp)->complex || (tmp)->obj->complex)
				return (NULL);
			else
				return ((tmp)->obj);
		}
		tmp = (tmp)->next;
	}
	return (NULL);
}

static bool		union_objs(t_objs **o_list, t_objs **u_list,
										t_union_tmp *data, t_union *complex)
{
	char	**tmp;
	int		count;

	count = 0;
	if (!(tmp = data->array))
		return (false);
	while (*tmp)
	{
		*u_list = (t_objs*)malloc(sizeof(t_objs));
		(*u_list)->next = NULL;
		(*u_list)->complex = NULL;
		if (((*u_list)->obj = find_objs(*o_list, ft_atoi(*tmp))) == NULL)
			return (false);
		(*u_list)->obj->solid = true;
		(*u_list)->obj->complex = complex;
		u_list = &(*u_list)->next;
		tmp++;
		++count;
	}
	if ((complex->type == (int)SOLID_IN ||
		complex->type == (int)SOLID_OUT) && count < 2)
		return (false);
	return (true);
}

void			change_union_matrix(t_union *complex)
{
	complex->transform = matrix_transform(complex->pos,
											complex->rot,
											complex->scale);
	complex->inverse = matrix_inverse(complex->transform);
	complex->transpose = matrix_transpose(complex->inverse);
}

t_union			*union_3d(t_union_tmp *data, t_objs **obj_list)
{
	t_union	*complex;

	complex = NULL;
	if (true)
	{
		complex = (t_union*)malloc(sizeof(t_union));
		complex->solid = false;
		complex->type = data->type;
		complex->mode = ROTATE;
		complex->axis = 'x';
		complex->pos = data->orientation.pos;
		complex->rot = data->orientation.rot;
		complex->scale = vector(MAX(data->orientation.scale.x, ACCURACY),
								MAX(data->orientation.scale.y, ACCURACY),
								MAX(data->orientation.scale.z, ACCURACY));
		change_union_matrix(complex);
		complex->obj_list = NULL;
		if (!union_objs(obj_list, &complex->obj_list, data, complex))
			delete_union(&complex);
	}
	return (complex);
}
