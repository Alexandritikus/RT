/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:50:25 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:06:46 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_intersect.h"

void	x_plane(t_ray ray, t_cube_tmp *tmp)
{
	tmp->tmin = (tmp->bmin.x - ray.origin.x) * tmp->r_dir.x;
	tmp->tmax = (tmp->bmax.x - ray.origin.x) * tmp->r_dir.x;
	tmp->nmin = vector(-1.0, 0.0, 0.0);
	tmp->nmax = vector(1.0, 0.0, 0.0);
	if (tmp->tmax < tmp->tmin)
	{
		ft_swap_double(&(tmp->tmin), &(tmp->tmax));
		tmp->nmin = vector(1.0, 0.0, 0.0);
		tmp->nmax = vector(-1.0, 0.0, 0.0);
	}
}

void	y_plane(t_ray ray, t_cube_tmp *tmp)
{
	tmp->tymin = (tmp->bmin.y - ray.origin.y) * tmp->r_dir.y;
	tmp->tymax = (tmp->bmax.y - ray.origin.y) * tmp->r_dir.y;
	tmp->nymin = vector(0.0, -1.0, 0.0);
	tmp->nymax = vector(0.0, 1.0, 0.0);
	if (tmp->tymax < tmp->tymin)
	{
		ft_swap_double(&(tmp->tymin), &(tmp->tymax));
		tmp->nymin = vector(0.0, 1.0, 0.0);
		tmp->nymax = vector(0.0, -1.0, 0.0);
	}
}

void	z_plane(t_ray ray, t_cube_tmp *tmp)
{
	tmp->tzmin = (tmp->bmin.z - ray.origin.z) * tmp->r_dir.z;
	tmp->tzmax = (tmp->bmax.z - ray.origin.z) * tmp->r_dir.z;
	tmp->nzmin = vector(0.0, 0.0, -1.0);
	tmp->nzmax = vector(0.0, 0.0, 1.0);
	if (tmp->tzmax < tmp->tzmin)
	{
		ft_swap_double(&(tmp->tzmin), &(tmp->tzmax));
		tmp->nzmin = vector(0.0, 0.0, 1.0);
		tmp->nzmax = vector(0.0, 0.0, -1.0);
	}
}

void	first_swap(t_cube_tmp *tmp)
{
	if (tmp->tymin > tmp->tmin)
	{
		tmp->tmin = tmp->tymin;
		tmp->nmin = tmp->nymin;
	}
	if (tmp->tymax < tmp->tmax)
	{
		tmp->tmax = tmp->tymax;
		tmp->nmax = tmp->nymax;
	}
}

void	second_swap(t_cube_tmp *tmp)
{
	if (tmp->tzmin > tmp->tmin)
	{
		tmp->tmin = tmp->tzmin;
		tmp->nmin = tmp->nzmin;
	}
	if (tmp->tzmax < tmp->tmax)
	{
		tmp->tmax = tmp->tzmax;
		tmp->nmax = tmp->nzmax;
	}
}
