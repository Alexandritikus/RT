/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:15:56 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:15:59 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void	choose_quartic_sign(t_root *root, t_quartic_tmp *t)
{
	if (SIGN(t->g1) == SIGN(t->g2))
	{
		t->gg = t->g1 + t->g2;
		t->g = (t->gg == 0) ? t->g1 - t->g2 : t->y / t->gg;
	}
	else
	{
		t->g = t->g1 - t->g2;
		t->gg = (t->g == 0) ? t->g1 + t->g2 : t->y / t->g;
	}
	if (SIGN(t->h1) == SIGN(t->h2))
	{
		t->hh = t->h1 + t->h2;
		t->h = (t->hh == 0) ? t->h1 - t->h2 : root->d / t->hh;
	}
	else
	{
		t->h = t->h1 - t->h2;
		t->hh = (t->h == 0) ? t->h1 + t->h2 : root->d / t->h;
	}
}

void	calculate_quartic_roots(t_root *root, t_quartic_tmp *t)
{
	double	r;

	t->nr = quadratic(1.0, t->gg, t->hh, t->quadr);
	t->nr += quadratic(1.0, t->g, t->h, t->quadr + t->nr);
	t->i = -1;
	while (++t->i < t->nr)
	{
		t->cubic[0] = root->a;
		t->cubic[1] = root->b;
		t->cubic[2] = root->c;
		root->roots_4[t->i] = polish_root(4, t->cubic, root->d, t->quadr[t->i]);
	}
	t->i = -1;
	while (++t->i < t->nr)
	{
		r = (((root->roots_4[t->i] + root->a) * root->roots_4[t->i] + root->b) *
				root->roots_4[t->i] + root->c) * root->roots_4[t->i] + root->d;
		if (fabs(r) > 1e-4)
		{
			root->roots_4[t->i] = root->roots_4[t->nr - 1];
			t->nr--;
			t->i--;
		}
	}
}
