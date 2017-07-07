# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/01 10:16:22 by oshudria          #+#    #+#              #
#    Updated: 2017/07/07 21:18:27 by oshudria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = $(shell uname -s)

CC = gcc
NAME = RT
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./includes/

SRC_PATH = ./srcs/
SRC_NAME = main.c \
		terminal_output/usage.c \
		terminal_output/progress_bar.c \
		hooks/expose_hook.c \
		hooks/key_hook.c \
		hooks/mouse_hook.c \
		hooks/general_hook.c \
		hooks/title.c \
		hooks/pic_list.c \
		hooks/menu_bar_button.c \
		hooks/create_image_file.c \
		hooks/key_hook_2.c \
		hooks/key_hook_camera.c \
		hooks/key_hook_creative.c \
		hooks/key_hook_creative_modify.c \
		hooks/key_hook_creative_color.c \
		hooks/stroboscope.c \
		print_menu/print_menu.c \
		print_menu/print_creative_mode.c \
		scene/camera.c \
		scene/lights.c \
		scene/object_3d.c \
		scene/triangle.c \
		scene/union_3d.c \
		scene/parsing/parse_scene.c \
		scene/parsing/get_scene_type.c \
		scene/parsing/create_scene_tmp_object.c \
		scene/parsing/update_scene_tmp.c \
		scene/parsing/update_obj_tmp.c \
		scene/parsing/update_light_tmp.c \
		scene/parsing/update_material.c \
		scene/parsing/texture_from_file.c \
		scene/parsing/update_scene.c \
		scene/parsing/update_mesh_tmp_1.c \
		scene/parsing/update_mesh_tmp_2.c \
		scene/parsing/face_from_string.c \
		scene/parsing/update_union_tmp.c \
		math/vector_1.c \
		math/vector_2.c \
		math/vector_3.c \
		math/vector_4.c \
		math/vector_5.c \
		math/matrix_1.c \
		math/matrix_2.c \
		math/matrix_3.c \
		math/matrix_4.c \
		math/basic_structures.c \
		color/color_1.c \
		color/color_2.c \
		materials/materials_1.c \
		materials/materials_2.c \
		materials/materials_3.c \
		materials/materials_4.c \
		materials/materials_5.c \
		materials/normal_map.c \
		materials/perlin_noise_part_1.c \
		materials/perlin_noise_part_2.c \
		materials/color_from_pixel.c \
		intersections/sphere.c \
		intersections/capsule.c \
		intersections/capsule_add.c \
		intersections/cone.c \
		intersections/cube.c \
		intersections/cube_add.c \
		intersections/cylinder.c \
		intersections/cylinder_add.c \
		intersections/disc.c \
		intersections/plane.c \
		intersections/triangle.c \
		intersections/tube.c \
		intersections/torus.c \
		intersections/moebius.c \
		intersections/moebius_add1.c \
		intersections/moebius_add2.c \
		intersections/roots.c \
		intersections/roots_2.c \
		intersections/roots_3.c \
		intersections/roots_4.c \
		intersections/roots_5.c \
		intersections/mesh.c \
		intersections/sky_box.c \
		intersections/bump_mapping.c \
		intersections/compose.c \
		intersections/solid_in.c \
		intersections/solid_out.c \
		intersections/paraboloid.c \
		bsp/boundaries.c \
		bsp/bsp_allocate.c \
		bsp/bsp_intersection.c \
		bsp/bsp.c \
		raytracing/draw_scene.c \
		raytracing/draw_scene_intersect.c \
		raytracing/draw_scene_intersect_2.c \
		raytracing/draw_scene_color.c \
		raytracing/draw_scene_diff_spec.c \
		raytracing/draw_scene_diff_spec_2.c \
		raytracing/draw_scene_reflect.c \
		raytracing/draw_scene_reflect_2.c \
		photo_filter/photo_filters.c \
		photo_filter/photo_filters_2.c \
		clear_memory/delete_environment.c \
		clear_memory/delete_image.c \
		clear_memory/delete_mesh.c \
		clear_memory/delete_obj_list.c \
		clear_memory/delete_scene.c \
		clear_memory/delete_skybox.c \
		clear_memory/delete_union.c \

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

LIBFT = ./libft/libft.a
LIBFT_INC = -I./libft/includes/

ifeq ($(UNAME), Darwin)
	ADDLIB = -lm -lpthread -lmlx -framework OpenGL -framework AppKit -O3
else ifeq ($(UNAME), Linux)
	ADDLIB = -lm -lpthread -lmlx -lX11 -lXext -O3
endif

COLOR_NONE = \033[0m
COLOR_YELLOW = \033[33m
COLOR_MAGENTA = \033[35m

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBFT) $(ADDLIB)
	@echo "$(COLOR_YELLOW)RT succesfully compiled.$(COLOR_NONE)"

$(OBJ_DIR)/%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(LIBFT_INC) $(INCLUDES) -o $@ -c $<

clean:
	make clean -C ./libft
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR_MAGENTA)RT clean done.$(COLOR_NONE)"

fclean: clean
	make fclean -C ./libft
	@$(RM) $(NAME)
	@echo "$(COLOR_MAGENTA)RT fclean done.$(COLOR_NONE)"

re: fclean all
