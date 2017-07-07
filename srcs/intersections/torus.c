/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:08:44 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/29 11:53:33 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void		intersect_torus_param(t_ray ray, t_intersect *j)
{
	t_torus_tmp	tmp;
	double		theta;
	double		phi;

	tmp.rr2 = RADIUS_OUT * RADIUS_OUT;
	tmp.r2 = RADIUS_IN * RADIUS_IN;
	tmp.q = vector_add(ray.origin, vector_mult_d(ray.direction, j->distance));
	tmp.qx2 = tmp.q.x * tmp.q.x;
	tmp.qy2 = tmp.q.y * tmp.q.y;
	tmp.qz2 = tmp.q.z * tmp.q.z;
	tmp.nx = 4 * tmp.q.x * (tmp.qx2 + tmp.qy2 + tmp.qz2 - tmp.r2 - tmp.rr2);
	tmp.ny = 4 * tmp.q.y * (tmp.qx2 + tmp.qy2 + tmp.qz2 - tmp.r2 - tmp.rr2);
	tmp.nz = 4 * tmp.q.z * (tmp.qz2 + tmp.qy2 + tmp.qz2 - tmp.r2 - tmp.rr2)
													+ 8 * tmp.rr2 * tmp.q.z;
	j->point = tmp.q;
	j->normal = vector(tmp.nx, tmp.ny, tmp.nz);
	theta = asin(tmp.q.z / RADIUS_IN);
	phi = asin(tmp.q.y / (RADIUS_OUT + RADIUS_IN * cos(theta)));
	j->u = 0.5 + phi / M_PI;
	j->v = 0.5 + theta / M_PI;
}

static void	torus_line(t_ray ray, t_root *roots)
{
	t_torus_tmp	tmp;
	t_vec		p;
	t_vec		d;

	p = ray.origin;
	d = ray.direction;
	tmp.rr2 = RADIUS_OUT * RADIUS_OUT;
	tmp.r2 = RADIUS_IN * RADIUS_IN;
	tmp.a = vector_dot(d, d);
	tmp.b = 2 * (vector_dot(p, d));
	tmp.y = vector_dot(p, p) - tmp.r2 - tmp.rr2;
	tmp.aa = 1.0 / (tmp.a * tmp.a);
	tmp.bb = 2 * tmp.a * tmp.b;
	tmp.cc = tmp.b * tmp.b + 2 * tmp.a * tmp.y + 4 * tmp.rr2 * d.z * d.z;
	tmp.dd = 2 * tmp.b * tmp.y + 8 * tmp.rr2 * p.z * d.z;
	tmp.ee = tmp.y * tmp.y + 4 * tmp.rr2 * p.z * p.z - 4 * tmp.rr2 * tmp.r2;
	roots->a = tmp.bb * tmp.aa;
	roots->b = tmp.cc * tmp.aa;
	roots->c = tmp.dd * tmp.aa;
	roots->d = tmp.ee * tmp.aa;
}

bool		intersect_torus(t_object *torus, t_ray ray, t_intersect *j)
{
	t_root		r;
	int			num_roots;
	double		t;
	int			i;

	torus_line(ray, &r);
	num_roots = quartic_roots(&r);
	if (num_roots == 0)
		return (false);
	t = INFINITY;
	i = -1;
	while (++i < num_roots)
		t = (r.roots_4[i] > 0 && r.roots_4[i] < t) ? r.roots_4[i] : t;
	if (isinf(t))
		return (false);
	j->ray = ray;
	j->is_inter = true;
	j->obj = torus;
	j->distance = t;
	return (true);
}
