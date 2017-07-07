/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 14:23:25 by oshudria          #+#    #+#             */
/*   Updated: 2017/05/24 10:40:57 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COLOR_H
# define RT_COLOR_H

# include "rt_math.h"

# define NTZ(x) (isnan((x)) ? 0.0 : (x))

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
	double		f;
}				t_color;

t_color			color(double r, double g, double b);
t_color			color_zero(void);
t_color			color_full(double r, double g, double b, double f);
t_color			color_mult(t_color col, double amount);
t_color			color_add(t_color col1, t_color col2);
t_color			clip(t_color color);
t_color			color_from_vector(t_vec vec);
t_color			color_mult_color(t_color col1, t_color col2);
int				rgb_to_int(t_color color);

#endif
