NAME = miniRT
NAME_BONUS = miniRT_bonus

INC_DIR = inc lib/libft/inc lib/minilibx-linux/
SRC_DIR = src
OBJ_DIR = obj
INC_BONUS_DIR = inc_bonus lib/libft/inc lib/minilibx-linux/
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

MATH_DIR = math
MINIRT_DIR = minirt
VALIDATION_DIR = validation
PARSER_DIR = parser

SRC = main.c \
	  free_memory.c \
	  $(MATH_DIR)/rt_math.c \
	  $(MATH_DIR)/rt_math2.c \
	  $(MATH_DIR)/rt_math3.c \
	  $(MATH_DIR)/rt_math4.c \
	  $(MATH_DIR)/rt_math_intersection.c \
	  $(MATH_DIR)/surface.c \
	  $(MINIRT_DIR)/env.c \
	  $(MINIRT_DIR)/window.c \
	  $(MINIRT_DIR)/img_buffer.c \
	  $(MINIRT_DIR)/key_hook.c \
	  $(MINIRT_DIR)/mouse_hook.c \
	  $(MINIRT_DIR)/raytrace.c \
	  $(MINIRT_DIR)/render.c \
	  $(VALIDATION_DIR)/input.c \
	  $(VALIDATION_DIR)/validate_objects.c \
	  $(VALIDATION_DIR)/validate_scene.c \
	  $(VALIDATION_DIR)/validate_properties.c \
	  $(VALIDATION_DIR)/validate_number_values.c \
	  $(PARSER_DIR)/parse_scene.c \
	  $(PARSER_DIR)/parse_objects.c \
	  $(PARSER_DIR)/parse_values.c \

SRC_BONUS = main_bonus.c \
	  free_memory_bonus.c \
	  $(MATH_DIR)/rt_math_bonus.c \
	  $(MATH_DIR)/rt_math2_bonus.c \
	  $(MATH_DIR)/rt_math3_bonus.c \
	  $(MATH_DIR)/rt_math4_bonus.c \
	  $(MATH_DIR)/rt_math_intersection_bonus.c \
	  $(MATH_DIR)/surface_bonus.c \
	  $(VALIDATION_DIR)/input_bonus.c \
	  $(VALIDATION_DIR)/validate_objects_bonus.c \
	  $(VALIDATION_DIR)/validate_scene_bonus.c \
	  $(VALIDATION_DIR)/validate_properties_bonus.c \
	  $(VALIDATION_DIR)/validate_number_values_bonus.c \
	  $(PARSER_DIR)/parse_scene_bonus.c \
	  $(PARSER_DIR)/parse_objects_bonus.c \
	  $(PARSER_DIR)/parse_values_bonus.c \

