/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiholkin <aiholkin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:23:02 by aiholkin          #+#    #+#             */
/*   Updated: 2017/05/29 11:53:46 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

static double	choose_mobi_root(double *roots, int ret, t_ray ray)
{
	int			i;
	t_vec		hit;

	i = 0;
	while (i < ret)
	{
		if (roots[i] > DBL_EPSILON)
		{
			hit = vector_add(vector_mult_d(ray.direction, roots[i]),
															ray.origin);
			if (inside(hit))
				return (roots[i]);
		}
		i++;
	}
	return (0);
}

static void		init_coeffs(t_moebius m, double *coeff)
{
	coeff[3] = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g - 2 * m.e
		* m.e * m.g + m.e * m.g * m.g;
	coeff[0] = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f - 2 *
		m.d * m.d * m.f
		+ m.d * m.f * m.f - 2 * m.b * m.f * m.a - m.d * m.a * m.a) / coeff[3];
	coeff[1] = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d + 3
		* m.e * m.d
		* m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f - 4 * m.e * m.d * m.f
		+ 2 * m.g * m.d
		* m.f + m.e * m.f * m.f - 2 * m.g * m.b * m.a - 2 * m.c * m.f * m.a -
		m.e * m.a * m.a) / coeff[3];
	coeff[2] = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d + 3
		* m.e * m.e
		* m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d - 2 * m.c * m.c * m.f -
		2 * m.e * m.e * m.f
		+ 2 * m.e * m.g * m.f - 2 * m.c * m.g * m.a) / coeff[3];
}

static t_vec	m_normal(t_vec real)
{
	t_vec		ret;

	ret.x = -2 * SIZE * real.z + 2 * real.x * real.y - 4 * real.x *
		real.z;
	ret.y = -0.5 + real.x * real.x + 3 * real.y * real.y - 4
		* real.y * real.z + real.z * real.z;
	ret.z = -2 * SIZE * real.x - 2 * real.x * real.x - 2 * real.y *
		real.y + 2 * real.y * real.z;
	return (ret);
}

void			intersect_moebius_param(t_ray ray, t_intersect *j)
{
	j->point = vector_add(ray.origin,
				vector_mult_d(ray.direction, j->distance));
	j->normal = m_normal(j->point);
}

bool			intersect_moebius(t_object *moebius, t_ray ray, t_intersect *j)
{
	double		a[4];
	double		root[3];
	t_moebius	m;
	t_vec		x;
	int			ret;

	x = ray.origin;
	m.a = SIZE;
	m.b = x.x;
	m.c = ray.direction.x;
	m.d = x.y;
	m.e = ray.direction.y;
	m.f = x.z;
	m.g = ray.direction.z;
	init_coeffs(m, a);
	ret = solve_cubic(a, root);
	j->distance = choose_mobi_root(root, ret, ray);
	if (j->distance <= 0)
		return (false);
	j->is_inter = true;
	j->obj = moebius;
	j->ray = ray;
	return (true);
}
