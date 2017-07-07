/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:11:04 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/31 16:19:52 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene.h"

t_tri	*triangle(t_vec v1, t_vec v2, t_vec v3)
{
	t_tri	*triangle;

	triangle = (t_tri*)malloc(sizeof(t_tri));
	triangle->v1 = v1;
	triangle->v2 = v2;
	triangle->v3 = v3;
	return (triangle);
}
