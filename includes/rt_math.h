/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:40:38 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:18:15 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include <math.h>

# define ACCURACY 0.0000001
# define RAD_COEF 0.01745

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_vec_i2
{
	int			x;
	int			y;
}				t_vec_i2;

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_matrix
{
	double		elem[4][4];
}				t_matrix;

t_vec			vector(double x, double y, double z);
t_vec			vector_zero(void);
t_vec			vector_one(double coord);
t_vec			vector_from_str(char *str);
t_vec			vector_div_d(t_vec vec, double d);
t_vec			vector_mult_d(t_vec vec, double m);
t_vec			vector_div_vec(t_vec v1, t_vec v2);
t_vec			vector_mult_vec(t_vec v1, t_vec v2);
t_vec			vector_add(t_vec v1, t_vec v2);
t_vec			vector_sub(t_vec v1, t_vec v2);
t_vec			vector_cross(t_vec v1, t_vec v2);
t_vec			vector_normalize(t_vec vec);
t_vec			vector_project(t_vec v1, t_vec v2);
t_vec			vector_negative(t_vec vector);
t_vec			vector_rotate(t_vec vec, t_vec rotate);
double			dist_to_dot(t_vec p1, t_vec p2);
double			vector_length(t_vec vec);
double			vector_dot(t_vec v1, t_vec v2);
double			vector_length2(t_vec vec);
t_vec2			vector2_zero(void);
t_vec2			vector2_from_str(char *str);
t_vec2			vector2(double x, double y);

t_matrix		zero_matrix(void);
t_matrix		identity_matrix(void);
t_matrix		matrix_from_vector(double *vector);
t_matrix		matrix_copy(t_matrix matrix);
t_matrix		matrix_transpose(t_matrix matrix);
t_matrix		matrix_transform(t_vec pos, t_vec rot, t_vec scale);
t_matrix		matrix_inverse(t_matrix matrix);
t_matrix		disc_rotate(double angle, t_vec vec);
t_vec			matrix_to_vector(t_matrix matrix, t_vec point, int toggle);

#endif
