/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:15:46 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:15:49 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static void	quartic_polish(t_root *root, t_quartic_tmp *t)
{
	t->cubic[0] = -2.0 * root->b;
	t->cubic[1] = root->b * root->b + root->a * root->c - 4 * root->d;
	t->cubic[2] = root->c * root->c - root->a * root->b * root->c +
											root->a * root->a * root->d;
	t->nr = cubic_roots(t->cubic, root->roots_4);
	if (t->nr == 1)
		t->y = polish_root(3, t->cubic, 0.0, root->roots_4[0]);
	else
	{
		if (root->b < 0 && root->d < 0)
			t->y = polish_root(3, t->cubic, 0.0, root->roots_4[2]);
		else
			t->y = polish_root(3, t->cubic, 0.0, root->roots_4[0]);
	}
	t->g1 = root->a / 2.0;
	t->h1 = (root->b - t->y) / 2.0;
}

static int	first_third(t_root *root, t_quartic_tmp *t)
{
	t->n = root->a * root->a - 4 * t->y;
	if (t->n <= 0)
		return (0);
	t->g2 = sqrt(t->n);
	if (t->g2 == 0)
		return (0);
	t->h2 = (root->a * ((root->b - t->y) / 2.0) - root->c) / t->g2;
	t->g2 /= 2.0;
	return (1);
}

static int	second_third(t_root *root, t_quartic_tmp *t)
{
	t->m = (root->b - t->y) * (root->b - t->y) - 4 * root->d;
	if (t->m <= 0)
		return (0);
	t->h2 = sqrt(t->m);
	if (t->h2 == 0)
		return (0);
	t->g2 = (root->a * t->h1 - root->c) / t->h2;
	t->h2 /= 2.0;
	return (1);
}

static int	quartic_third(t_root *r, t_quartic_tmp *t)
{
	t->n = r->a * r->a - 4 * t->y;
	t->m = (r->b - t->y) * (r->b - t->y) - 4 * r->d;
	t->en = r->b * r->b + 2 * fabs(r->b * t->y) + t->y * t->y + 4 * fabs(r->d);
	t->em = r->a * r->a + 4 * fabs(t->y);
	if (t->m * t->en > t->n * t->em)
	{
		if (t->m <= 0)
			return (0);
		t->h2 = sqrt(t->m);
		if (t->h2 == 0)
			return (0);
		t->g2 = (r->a * t->h1 - r->c) / t->h2;
		t->h2 /= 2.0;
	}
	else
	{
		if (t->n <= 0)
			return (0);
		t->g2 = sqrt(t->n);
		if (t->g2 == 0)
			return (0);
		t->h2 = (r->a * ((r->b - t->y) / 2.0) - r->c) / t->g2;
		t->g2 /= 2.0;
	}
	return (1);
}

int			quartic_roots(t_root *root)
{
	t_quartic_tmp	t;

	quartic_polish(root, &t);
	if (t.y < 0)
	{
		if (!first_third(root, &t))
			return (0);
	}
	else if (t.y > 0 && root->d > 0 && root->b < 0)
	{
		if (!second_third(root, &t))
			return (0);
	}
	else
	{
		if (!quartic_third(root, &t))
			return (0);
	}
	choose_quartic_sign(root, &t);
	calculate_quartic_roots(root, &t);
	return (t.nr);
}
