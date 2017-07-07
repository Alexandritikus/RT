/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:42:11 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:16:13 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

int	quadratic_roots(t_root *root)
{
	double	d;
	double	q;

	if (root->a == 0)
	{
		if (root->b == 0)
			return (0);
		else
			root->roots_2[0] = -root->c / root->b;
		return (1);
	}
	d = root->b * root->b - 4 * root->a * root->c;
	if (d > 0)
	{
		q = -(root->b + SIGN(root->b) * sqrt(d)) / 2.0;
		root->roots_2[0] = q / root->a;
		if (q != 0)
			root->roots_2[1] = root->c / q;
		else
			root->roots_2[1] = root->roots_2[0];
		return (2);
	}
	return (0);
}

int	quadratic(double a, double b, double c, double roots[4])
{
	double	d;
	double	q;

	if (a == 0)
	{
		if (b == 0)
			return (0);
		else
			roots[0] = -c / b;
		return (1);
	}
	d = b * b - 4 * a * c;
	if (d > 0)
	{
		q = -(b + SIGN(b) * sqrt(d)) / 2.0;
		roots[0] = q / a;
		if (q != 0)
			roots[1] = c / q;
		else
			roots[1] = roots[0];
		return (2);
	}
	return (0);
}
