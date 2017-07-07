/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:58:59 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/14 13:42:10 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INTERSECT_H
# define RT_INTERSECT_H

# include "rt_scene.h"

# define SIZE			1.0
# define RADIUS			1.0
# define RADIUS_IN		0.5
# define RADIUS_OUT		1.0
# define HEIGHT			1.0

# define DBL_EPSILON	2.20e-16
# define SQRT3			1.73205

# define SIGN(x) (((x) < 0) ? -1 : 1)

typedef struct	s_ray
{
	t_vec		origin;
	t_vec		direction;
}				t_ray;

typedef struct	s_intersect
{
	bool		is_normal;
	bool		is_inter;
	double		distance;
	double		u;
	double		v;
	t_vec		pu;
	t_vec		pv;
	t_ray		ray;
	t_vec		point;
	t_vec		normal;
	t_vec		n;
	t_vec		hit;
	t_object	*obj;
	int			type;
}				t_intersect;

typedef struct	s_disc
{
	t_vec		pos;
	double		r;
}				t_disc;

typedef struct	s_sphere
{
	t_vec		pos;
	double		r;
}				t_sphere;

typedef struct	s_cube_tmp
{
	t_vec		r_dir;
	t_vec		bmin;
	t_vec		bmax;
	double		tmin;
	double		tmax;
	t_vec		nmin;
	t_vec		nmax;
	double		tymin;
	double		tymax;
	t_vec		nymin;
	t_vec		nymax;
	double		tzmin;
	double		tzmax;
	t_vec		nzmin;
	t_vec		nzmax;
}				t_cube_tmp;

typedef struct	s_moebius
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
}				t_moebius;

typedef struct	s_mob
{
	double		scale;
	double		max;
}				t_mob;

typedef struct	s_cubic
{
	double		q;
	double		r;
	double		bq;
	double		br;
	double		bq3;
	double		br2;
	double		cr2;
	double		cq3;
	double		sqrtbq;
	double		sgnbr;
	double		ratio;
	double		theta;
	double		norm;
	double		r0;
	double		r1;
	double		r2;
	double		ba;
	double		bb;
	int			i;
}				t_cubic;

typedef struct	s_root
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		roots_2[2];
	double		roots_4[4];
}				t_root;

typedef struct	s_solid_in_tmp
{
	t_intersect	j;
	t_intersect	k;
	t_intersect	u;
	t_intersect	v;
	t_ray		new_ray;
	int			id;
	double		t;
	bool		inter_a;
	bool		inter_b;
}				t_solid_in_tmp;

typedef struct	s_mesh_temp
{
	t_vec		a;
	t_vec		b;
	t_vec		c;
	t_vec		e1;
	t_vec		e2;
	t_vec		pp;
	t_vec		tt;
	t_vec		qq;
	bool		intersected;
	double		t;
	double		u;
	double		v;
	double		det;
	double		prev_t;
	double		p_e1;
}				t_mesh_temp;

typedef struct	s_quartic_tmp
{
	double		cubic[3];
	double		quadr[4];
	double		h;
	double		h1;
	double		h2;
	double		hh;
	double		g;
	double		g1;
	double		g2;
	double		gg;
	double		n;
	double		m;
	double		en;
	double		em;
	double		y;
	int			i;
	int			nr;
}				t_quartic_tmp;

typedef struct	s_torus_tmp
{
	t_vec		q;
	double		rr2;
	double		r2;
	double		a;
	double		b;
	double		y;
	double		aa;
	double		bb;
	double		cc;
	double		dd;
	double		ee;
	double		qx2;
	double		qy2;
	double		qz2;
	double		nx;
	double		ny;
	double		nz;
}				t_torus_tmp;

typedef struct	s_cubic_tmp
{
	double		u;
	double		v;
	double		w;
	double		s;
	double		t;
	double		cosk;
	double		sink;
	double		p_3;
	double		k;
}				t_cubic_tmp;

typedef struct	s_polish_tmp
{
	double		x;
	double		y;
	double		dydx;
	double		dx;
	double		lastx;
	double		lasty;
	double		cs[4];
}				t_polish_tmp;

t_intersect		intersection_zero(void);
/*
** sphere
*/
void			intersect_sphere_param(t_ray ray, t_intersect *j);
bool			intersect_sphere(t_object *sphere, t_ray ray, t_intersect *j);
/*
** capsule
*/
void			intersect_capsule_param(t_ray ray, t_intersect *j);
bool			intersect_capsule(t_object *capsule, t_ray ray, t_intersect *j);
t_sphere		cyl_sphere(t_vec pos, double r);
bool			intersect_cyl_sphere(t_sphere sph, t_ray ray, t_intersect *j);
/*
** cone
*/
bool			intersect_cone(t_object *cone, t_ray ray, t_intersect *j);
/*
** cube
*/
void			intersect_cube_param(t_ray ray, t_intersect *j);
bool			intersect_cube(t_object *cube, t_ray ray, t_intersect *j);
void			x_plane(t_ray ray, t_cube_tmp *tmp);
void			y_plane(t_ray ray, t_cube_tmp *tmp);
void			z_plane(t_ray ray, t_cube_tmp *tmp);
void			first_swap(t_cube_tmp *tmp);
void			second_swap(t_cube_tmp *tmp);
/*
** cylinder
*/
void			intersect_cylinder_param(t_ray ray, t_intersect *j);
bool			intersect_cylinder(t_object *cyl, t_ray ray, t_intersect *j);
t_disc			cyl_disc(t_vec pos, double r);
bool			intersect_cyl_disc(t_disc disc, t_ray ray, t_intersect *j);
/*
** disc
*/
void			intersect_disc_param(t_ray ray, t_intersect *j);
bool			intersect_disc(t_object *disc, t_ray ray, t_intersect *j);
/*
** plane
*/
void			intersect_plane_param(t_intersect *j);
bool			intersect_plane(t_object *plane, t_ray ray, t_intersect *j);
/*
** triangle
*/
bool			intersect_triangle(t_object *tri, t_ray ray, t_intersect *j);
/*
** tube
*/
void			intersect_tube_param(t_ray ray, t_intersect *j);
bool			intersect_tube(t_object *tube, t_ray ray, t_intersect *j);
/*
** paraboloid
*/
bool			intersect_paraboloid(t_object *parab, t_ray r, t_intersect *j);
/*
** torus
*/
void			intersect_torus_param(t_ray ray, t_intersect *j);
bool			intersect_torus(t_object *torus, t_ray ray, t_intersect *j);
/*
** moebius strip
*/
void			intersect_moebius_param(t_ray ray, t_intersect *j);
bool			intersect_moebius(t_object *moebius, t_ray ray, t_intersect *j);
int				solve_cubic(double *a, double *r);
int				inside(t_vec h);
/*
** mesh
*/
bool			intersect_mesh(t_object *m, t_ray r, t_intersect *j, t_poly *p);
int				boundaries_intersect(t_boundaries bound, t_ray ray);
t_intersect		get_branch_intersect(t_bsp *bsp, t_ray ray, t_object *mesh);
t_intersect		get_closest_intersect(t_bsp *bsp, t_ray ray, t_object *mesh);
t_intersect		intersection_zero(void);
/*
** sky box
*/
t_color			bg_color(t_scene *scene, t_ray ray);
/*
** union
*/
void			intersect_compose(t_ray ray, t_intersect *inter, t_objs *cur);
void			intersect_solid_in(t_ray ray, t_intersect *inter, t_objs *cur);
void			intersect_solid_out(t_ray ray, t_intersect *inter, t_objs *obj);
/*
** roots
*/
int				quadratic_roots(t_root *root);
int				quartic_roots(t_root *root);
int				quadratic(double a, double b, double c, double roots[4]);
int				cubic_roots(double c[3], double roots[3]);
double			polish_root(int degree, double c[3], double d, double root);
void			choose_quartic_sign(t_root *root, t_quartic_tmp *t);
void			calculate_quartic_roots(t_root *root, t_quartic_tmp *t);
/*
** bump mapping
*/
t_vec			bump(t_intersect inter);

#endif
