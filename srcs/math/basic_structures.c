/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:22:25 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/09 17:19:34 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "libft.h"

static char	*skip_non_number(char *ptr)
{
	char	*current;

	current = ptr;
	while (*current != '\0')
	{
		if (ft_isdigit(*current))
			break ;
		if (*current == '-' && ft_isdigit(*(current + 1)))
			break ;
		current++;
	}
	return (current);
}

static char	*skip_number(char *ptr)
{
	char	*current;

	current = ptr;
	if (*current == '-')
		current++;
	while (*current != '\0' && (ft_isdigit(*current) || *current == '.'))
	{
		if (*current == '.' && !ft_isdigit(*(current + 1)))
			break ;
		current++;
	}
	return (current);
}

t_vec		vector_from_str(char *str)
{
	t_vec	result;
	char	*p;

	result = vector_zero();
	if ((p = skip_non_number(str)))
	{
		result.x = ft_atof(p);
		p = skip_number(p);
	}
	if ((p = skip_non_number(p)))
	{
		result.y = ft_atof(p);
		p = skip_number(p);
	}
	if ((p = skip_non_number(p)))
		result.z = ft_atof(p);
	return (result);
}

t_vec2		vector2_from_str(char *str)
{
	t_vec2	result;
	char	*p;

	result = vector2_zero();
	if ((p = skip_non_number(str)))
	{
		result.x = ft_atof(p);
		p = skip_number(p);
	}
	if ((p = skip_non_number(p)))
		result.y = ft_atof(p);
	return (result);
}
