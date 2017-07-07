/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_from_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 10:26:42 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 20:44:37 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

static char	*skip_face(char *ptr)
{
	char	*current;

	current = ptr;
	while (*current && *current != ' ' && *current != '\t')
		current++;
	return (current);
}

static char	*skip_number(char *ptr)
{
	char	*current;

	current = ptr;
	while (ft_isdigit(*current))
		current++;
	if (*current == '/')
	{
		if (*(current + 1) != '\0')
			return (++current);
	}
	return (NULL);
}

static char	*get_current_vec_ptr(char *str, int current_vec_number)
{
	char	*ptr;
	int		cur_index;

	ptr = str;
	cur_index = 0;
	while (*ptr && cur_index < current_vec_number)
	{
		if (ft_isdigit(*ptr))
		{
			cur_index += 1;
			if (cur_index < current_vec_number)
			{
				ptr = skip_face(ptr);
				continue ;
			}
			else
				return (ptr);
		}
		ptr++;
	}
	return (NULL);
}

t_vec		vector_from_face(char *buf, int n)
{
	char	*ptr;
	t_vec	vec;

	vec = vector(1, 1, 1);
	if ((ptr = get_current_vec_ptr(buf, n)))
	{
		vec.x = MAX(1, ft_atoi(ptr));
		ptr = skip_number(ptr);
		if (ptr)
		{
			if (ft_isdigit(*ptr))
			{
				vec.y = MAX(1, ft_atoi(ptr));
				ptr = skip_number(ptr);
				if (ptr && ft_isdigit(*ptr))
					vec.z = MAX(1, ft_atoi(ptr));
			}
			else if (ft_isdigit(*(ptr + 1)))
			{
				ptr++;
				vec.z = MAX(1, ft_atoi(ptr));
			}
		}
	}
	return (vec);
}
