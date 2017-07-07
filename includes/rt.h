/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:47:50 by oshudria          #+#    #+#             */
/*   Updated: 2017/07/07 11:36:48 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <pthread.h>
# include "mlx.h"
# include "rt_intersect.h"
# include <stdio.h>

# ifdef __APPLE__
#  include "mac_keymap.h"
# elif __linux__
#  include "linux_keymap.h"
# endif

# define PROJECT_NAME "RT"
# define TITLE "title.xpm"
# define PIC_LIST "pic_list.xpm"
# define MENU "menu_bar.xpm"

/*
** colors for bash
*/
# define BLACK_BACK_ON "\e[48;5;0m"
# define RED_PRINT_ON "\e[38;5;196m"
# define PURPLE_PRINT_ON "\e[38;5;13m"
# define YELLOW_PRINT_ON "\e[38;5;226m"
# define COLOR_PRINT_OFF "\e[0m"

/*
** thread number for raytracing
*/
# define N_THREAD	4

/*
** colors for mlx_string_put
*/
# define WHITE	0xFFFFFF
# define BLACK	0x000000
# define GREY	0x888888
# define RED	0xB21031
# define GREEN	0x388C54

/*
** mlx hook flags
*/
# define DESTROY_NOTIFY			17
# define STRUCTURE_NOTIFY_MASK	1L<<17

/*
** image param
*/
# define SW_MENU	300

/*
** environments parameters
*/
# define MODE_TITLE 	1
# define MODE_PIC_LIST	2
# define MODE_VIEW 		3
# define MODE_CREATE	4

/*
** camera param, it need for manage camera view
*/
# define ANGLE	tan(50 * RAD_COEF / 2)

/*
** list of scenes
*/
# define SCENE_1 "maps/scene1.rt"
# define SCENE_2 "maps/scene2.rt"
# define SCENE_3 "maps/scene3.rt"
# define SCENE_4 "maps/scene4.rt"
# define SCENE_5 "maps/scene5.rt"
# define SCENE_6 "maps/scene6.rt"
# define SCENE_7 "maps/scene7.rt"
# define SCENE_8 "maps/scene8.rt"
# define SCENE_9 "maps/scene9.rt"
# define SCENE_10 "maps/scene10.rt"
# define SCENE_11 "maps/scene11.rt"
# define SCENE_12 "maps/scene12.rt"
# define SCENE_13 "maps/scene13.rt"
# define SCENE_14 "maps/scene14.rt"
# define SCENE_15 "maps/scene15.rt"

/*
** main structures
*/
typedef struct		s_env
{
	int				sw;
	int				sh;
	int				sw_image;
	double			aspect_ratio;
	void			*mlx;
	void			*win;
	void			*title;
	void			*pic_list;
	void			*menu;
	t_img			*filter;
	t_img			*dublicate_1;
	t_img			*dublicate_2;
	int				active;
	int				redraw;
	int				mode;
	int				thread_progress;
	t_scene			*scene;
}					t_env;

typedef struct		s_draw
{
	int				thread_id;
	t_env			*env;
}					t_draw;
/*
** temporary structures
*/
typedef struct		s_inter_tri_tmp
{
	double			len_rd;
	t_vec			e1;
	t_vec			e2;
	t_vec			h;
	t_vec			s;
	t_vec			q;
	double			a;
	double			u;
	double			v;
	double			t;
}					t_inter_tri_tmp;

typedef struct		s_inter_cyl_tmp
{
	t_vec			alpha;
	t_vec			beta;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			root;
}					t_inter_cyl_tmp;

typedef struct		s_tmp_ssaa
{
	double			pixel_width;
	double			sample_width;
	double			sample_weight;
	double			sample_x;
	double			sample_y;
	double			ray_x;
	double			ray_y;
}					t_tmp_ssaa;

typedef struct		s_res
{
	t_vec2			res;
	char			*pics;
	char			*title;
	char			*menu;
}					t_res;

typedef struct		s_refr_tmp
{
	t_vec			normal;
	double			ci;
	double			ct;
	double			n1;
	double			n2;
	double			nr;
	double			a;
	double			b;
}					t_refr_tmp;

typedef struct		s_dif_tmp
{
	t_vec			light_pos;
	t_vec			light_dir;
	t_vec			surf_light;
	t_vec			surf_eye;
	t_vec			halfway;
	t_ray			ray;
	t_objs			*cur;
	t_color			color;
	t_intersect		inter;
	bool			flag;
	bool			slide;
	double			light_dist;
	double			distance_to_light;
	double			dif_br;
	double			spec_br;
	double			len;
}					t_dif_tmp;

typedef struct		s_refl_tmp
{
	t_ray			refl_ray;
	t_ray			refr_ray;
	t_ray			reflected;
	t_color			refl_color;
	t_color			refr_color;
	double			refl_percent;
	double			refr_percent;
}					t_refl_tmp;
/*
** hook functions
*/
int					expose_hook(t_env *env);
int					key_hook(int key, t_env *env);
int					key_middle_top(t_env *env, int key);
int					key_camera(t_scene *scene, int key, int *redraw);
int					key_creative(t_env *env, int key);
int					color_manipulate(t_object *active, int key, int *redraw);
int					mouse_hook(int key, int x, int y, t_env *env);
int					home_button(int x, int y, int start);
int					scene_list_button(int x, int y, int start);
int					exit_x(t_env *env);
int					check_title(int x, int y, t_env *env);
int					check_pic_list(int x, int y, t_env *env);
void				print_menu(t_env *env);
void				print_creative_mode(void *mlx, void *win, int x_start,
																	t_env *env);
void				create_img_file(t_img *pic);
void				axis_modify(t_object *active, bool sign);
void				mode_modify(t_object *active, bool sign);
int					show_stereo(t_env *env);
void				dublicate_image(t_env *env);
/*
** raytracing
*/
t_ray				ray(t_vec orig, t_vec dir);
void				draw_scene(t_env *env);
/*
** intersections
*/
t_color				intersect_color(t_scene *scene, t_ray ray);
t_color				intersect_object(t_scene *scene, t_ray ray, int rr);
t_color				color_estimate(t_scene *scene, t_intersect obj, int rr);
t_color				get_intersection_color(t_intersect inter);
t_color				get_diff_spec_color(t_color c, t_scene *s, t_intersect o);
t_color				lighting(t_vec light_pos, t_light *light, t_color col,
															t_intersect i_obj);
t_color				get_light_color(t_light *light, t_vec light_pos, t_vec p);
t_vec				get_light_direction(t_light *light, t_vec l_pos, t_vec p);
t_vec				get_position(t_light *l);
void				intersect_primitive(t_ray r, t_intersect *inter, t_objs *o);
void				intersect_union(t_ray r, t_intersect *inter, t_objs *o);
void				calculate_param(t_ray ray, t_intersect *inter);
void				intersect_param(t_ray ray, t_intersect *inter);
bool				intersect_distance(t_object *obj, t_ray r, t_intersect *i);
/*
** reflection && refraction
*/
t_color				get_reflect_color(t_scene *scene, t_intersect obj, int rr);
double				get_reflectance(t_intersect inter_obj);
bool				refract(t_intersect inter_obj, t_ray *refracted);
t_ray				reflect(t_intersect inter_obj);
bool				reflect_perturbed(t_intersect obj, t_ray refl, t_ray *r_r);
/*
** terminal output: usage and progress bar
*/
void				ft_usage(char *binary);
void				whaiting_message(void);
void				thread_progress_count(int n, int *thread_progress);
void				*progress_bar(void *param);
/*
** photo filters
*/
void				use_photo_filter(t_env *env);
int					use_grey_scale(t_color color_rgb);
int					use_negative(t_color color_rgb);
int					use_black_and_white(t_color rgb_col, t_color av_color);
int					use_sepia(t_color rgb);
int					use_warm(t_color rgb);
/*
** clear memory
*/
void				fix_scene_list(t_env *env);
void				delete_image(t_img **img, void *img_ptr, void *mlx);
void				delete_skybox(t_sky_box **bg, void *mlx);
void				delete_scene(t_scene **scene, void *mlx);
void				delete_obj_list(t_objs **head, void *mlx);
void				delete_object(t_objs **object, void *mlx);
void				delete_union(t_union **complex);
void				delete_poly_list(t_poly **poly_list);
void				delete_bsp_tree(t_bsp **tree);
void				delete_mesh(t_mesh **mesh);
void				delete_environment(t_env *env);

#endif
