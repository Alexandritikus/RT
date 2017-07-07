/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_materials.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:16:39 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/15 12:34:23 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATERIALS_H
# define RT_MATERIALS_H

# include <stdbool.h>
# include "rt_color.h"

/*
** interactions with light
*/
# define NOT_SHINY 				-1
# define NOT_REFLECTIVE 		-1
# define NOT_REFRACTIVE			-1
# define AIR_REFRACTIVE_INDEX	1

/*
** materials type define
*/
# define AIR		1
# define CHECKBOARD	2
# define CRISSCROSS	3
# define GLASS		4
# define MARBLE		5
# define SHINYCOLOR	6
# define TURBULENCE	7
# define WOOD		8
# define FLATCOLOR	9

/*
** transparency mode for texture
*/
# define M_G	1
# define M_R	2
# define M_B	3

/*
** main structures
*/
typedef struct	s_img
{
	void		*img;
	char		*adr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_noise
{
	int			noise[512];
}				t_noise;

typedef struct	s_norm_map
{
	t_noise		perlin;
	double		scale;
	double		amount;
}				t_norm_map;

typedef struct	s_material
{
	int			type;
	bool		is_normal;
	bool		slide;
	bool		cut;
	int			trans_mod;
	t_norm_map	normal_map;
	t_noise		perlin;
	t_color		color1;
	t_color		color2;
	t_color		color3;
	double		scale;
	double		shininess;
	double		reflectivity;
	double		refractive;
	double		bump_scale;
	t_img		*texture;
	t_img		*bump_map;
}				t_material;
/*
** temporary structure for the norm
*/
typedef struct	s_noise_tmp
{
	int			xx;
	int			yy;
	int			zz;
	double		u;
	double		v;
	double		w;
	int			a;
	int			aa;
	int			b;
	int			ab;
	int			ba;
	int			bb;
}				t_noise_tmp;

typedef struct	s_mat_tmp
{
	double		x;
	double		y;
	double		z;
	double		coef_a;
	double		coef_b;
	double		coef_c;
	int			level;
}				t_mat_tmp;

t_material		material_base(void);
t_material		fix_material(t_material material);
t_vec			mater_modify_normal(t_material mat, t_vec norm, t_vec p);
t_vec			map_modify_normal(t_norm_map map, t_vec norm, t_vec p);
t_color			get_afgs_color(t_material material, t_vec point);
t_color			get_checkerboard_color(t_material material, t_vec point);
t_color			get_marble_color(t_material material, t_vec point);
t_color			get_turbulence_color(t_material material, t_vec point);
t_color			get_wood_color(t_material material, t_vec point);
t_color			get_crisscross_color(t_material material, t_vec point);
t_color			color_from_pixel(t_img *pic, int x, int y);
t_norm_map		normal_map(double scale, double amount);
t_noise			perlin_noise(void);
double			noise(t_noise perlin, double x, double y, double z);
double			get_shininess(t_material material);
double			get_reflectivity(t_material material);
double			get_refractive(t_material material);
bool			check_texture_param(t_material material, t_color obj_col);

#endif
