/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 10:31:47 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 12:25:35 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_H
# define RT_SCENE_H

# include <fcntl.h>
# include "libft.h"
# include "rt_materials.h"
# include "mlx.h"

/*
** object type
*/
# define LIGHT		100
# define UNION		200
# define MESH		42
# define SCENE		0
# define SPHERE		1
# define CYLINDER	2
# define CONE		3
# define TRIANGLE	4
# define PLANE		5
# define DISC		6
# define TORUS		7
# define CUBE		8
# define TUBE		9
# define CAPSULE	10
# define MOEBIUS	11
# define PARABOLOID	12

/*
** active object modes (rotate, translate, scale)
*/
# define ROTATE		1
# define TRANSLATE	2
# define SCALE		3

/*
** active color (color1, color2, color3)
*/
# define COLOR_1	1
# define COLOR_2	2
# define COLOR_3	3

/*
** polygon face type
*/
# define V_ONLY		1
# define V_NORM		3

/*
** union types
*/
# define SOLID_IN	22
# define SOLID_OUT	33
# define COMPOSE	44

/*
** Light types
*/
# define BASE_L		66
# define POINT_L	99
# define DIR_L		88
# define SPOT_L		77

/*
** photo filters
*/
# define NONE			0
# define GREYSCALE		1
# define B_W			2
# define NEGATIVE		3
# define SEPIA			4
# define WARM			5
# define MOTION_BLUR	6

/*
** main structures
*/
typedef struct		s_camera
{
	t_vec			position;
	t_vec			look_at;
	t_vec			rotation;
	t_vec			up;
	t_matrix		view;
}					t_camera;

typedef struct		s_tri
{
	t_vec			v1;
	t_vec			v2;
	t_vec			v3;
}					t_tri;

typedef struct		s_boundaries
{
	t_vec			min;
	t_vec			max;
}					t_boundaries;

typedef struct		s_poly
{
	t_tri			*triangle;
	t_tri			*normal;
	t_boundaries	bounds;
	struct s_poly	*next;
}					t_poly;

typedef struct		s_bsp
{
	int				depth;
	int				axis_retries;
	char			axis;
	t_boundaries	bounds;
	t_poly			*poly_list;
	struct s_bsp	*left;
	struct s_bsp	*right;
}					t_bsp;

typedef struct		s_mesh
{
	int				face_type;
	t_poly			*polygon;
	double			radius;
	t_bsp			*bsp;
}					t_mesh;

typedef struct		s_union
{
	bool			solid;
	int				type;
	int				mode;
	char			axis;
	t_vec			pos;
	t_vec			rot;
	t_vec			scale;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	struct s_objs	*obj_list;
}					t_union;

typedef struct		s_object
{
	int				type;
	int				mode;
	int				color;
	char			axis;
	bool			solid;
	t_vec			pos;
	t_vec			rot;
	t_vec			scale;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	t_material		material;
	t_mesh			*mesh;
	t_union			*complex;
}					t_object;

typedef struct		s_objs
{
	t_object		*obj;
	t_union			*complex;
	struct s_objs	*next;
}					t_objs;

typedef struct		s_light
{
	t_vec			position;
	t_vec			falloff;
	t_vec			vertex;
	t_vec			normal;
	t_vec			perp;
	t_color			color;
	int				type;
	double			radius;
	double			intensity;
	struct s_light	*next;
}					t_light;

typedef struct		s_sky_box
{
	t_img			*front;
	t_img			*top;
	t_img			*bottom;
	t_img			*back;
	t_img			*right;
	t_img			*left;
}					t_sky_box;

typedef struct		s_scene
{
	char			*title;
	t_img			*pic;
	t_camera		*camera;
	t_objs			*obj_list;
	t_object		*active;
	t_light			*light;
	t_sky_box		*bg;
	t_color			bg_color;
	bool			effects;
	bool			antialias;
	int				ssaa;
	int				max_reflections;
	int				shadow_samples;
	int				lvl;
	int				m_blur_k;
	int				filter;
	double			ambient_light;
	struct s_scene	*next;
	struct s_scene	*prev;
}					t_scene;
/*
**temporary structures for parsing
*/
typedef struct		s_scene_tmp
{
	bool			effects;
	int				ssaa;
	int				focus_depth;
	int				max_reflections;
	int				shadow_samples;
	t_vec			cam_position;
	t_vec			cam_look_at;
	t_vec			cam_rotation;
	char			*sky_box_link;
	t_sky_box		*bg;
	t_color			bg_color;
}					t_scene_tmp;

typedef struct		s_light_tmp
{
	t_vec			position;
	t_vec			vertex;
	t_color			color;
	int				intensity;
	int				type;
	double			radius;
}					t_light_tmp;

typedef struct		s_orient
{
	t_vec			pos;
	t_vec			rot;
	t_vec			scale;
}					t_orient;

typedef struct		s_vert
{
	t_vec			vertex;
	struct s_vert	*next;
	struct s_vert	*prev;
}					t_vert;

typedef struct		s_face
{
	t_vec			v1;
	t_vec			v2;
	t_vec			v3;
	struct s_face	*next;
}					t_face;

typedef struct		s_mesh_tmp
{
	int				n_vertex;
	int				n_normal;
	t_vert			*vertex_head;
	t_vert			*vertex;
	t_vert			*normal_head;
	t_vert			*normal;
	t_face			*face_list;
}					t_mesh_tmp;

typedef struct		s_obj_tmp
{
	bool			solid;
	char			*mesh_link;
	t_mesh			*mesh;
	t_orient		orientation;
	t_material		material;
	double			torus_in_radius;
}					t_obj_tmp;

typedef struct		s_union_tmp
{
	int				type;
	t_orient		orientation;
	char			**array;
}					t_union_tmp;

typedef struct		s_scene_obj
{
	bool			status;
	t_scene_tmp		*scene_data;
	t_light_tmp		*light_data;
	t_obj_tmp		*obj_data;
	t_union_tmp		*union_data;
}					t_scene_obj;
/*
** parsing
*/
t_scene				*parse_scene(char *file_name, void *mlx, int sw, int sh);
int					get_scene_type(const char *buf, int prev_type);
t_scene_obj			*create_scene_object(int type);
t_img				*initialize_img(void *mlx, int width, int height);
t_img				*texture_from_file(char *buf, void *mlx);
t_img				*img_from_xpm(char *file_name, void *mlx);
void				update_scene_tmp(t_scene_tmp **data, char *buf, void *mlx);
void				update_obj_tmp(t_obj_tmp **d, char *buf, void *mlx, int t);
void				update_material(t_material *material, char *buf, void *mlx);
void				update_light_tmp(t_light_tmp **data, char *buf);
void				update_union_tmp(t_union_tmp **union_data, char *buf);
void				update_scene(t_scene_obj **s_obj, t_scene **s, int *t);
void				update_mesh_data(char *buf, t_mesh_tmp **data);
t_vec				vector_from_face(char *buf, int n);
t_mesh				*create_mesh(t_mesh_tmp *data);
t_sky_box			*get_sky_box(char *link, void *mlx);
/*
** object create and modify
*/
t_camera			*camera(t_vec pos, t_vec look_at, t_vec rotation);
void				calculate_view(t_camera *cam);
void				change_object_matrix(t_object *object);
void				change_union_matrix(t_union *complex);
t_union				*union_3d(t_union_tmp *data, t_objs **obj_list);
t_object			*object_3d(int t, t_orient o, t_material m, bool solid);
t_tri				*triangle(t_vec v1, t_vec v2, t_vec v3);
/*
** bsp tree
*/
t_bsp				*bsp_tree(int depth, char axis, t_poly *objects);
double				split_value(t_boundaries bound, char axis);
t_boundaries		boundaries();
void				mesh_update(t_object *obj);
void				build(t_bsp *bspp);
void				bsp_alloc(t_bsp *bspp, t_poly **l, t_poly **r);
int					count_obj(t_poly *obj);

#endif
