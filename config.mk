NAME = miniRT
NAME_BONUS = miniRT_bonus

INC_DIR = inc lib/libft/inc lib/minilibx-linux/
SRC_DIR = src
OBJ_DIR = obj
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

MATH_DIR = math
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
	  $(VALIDATION_DIR)/input.c \
	  $(VALIDATION_DIR)/validate_objects.c \
	  $(VALIDATION_DIR)/validate_scene.c \
	  $(VALIDATION_DIR)/validate_properties.c \
	  $(VALIDATION_DIR)/validate_number_values.c \
	  $(PARSER_DIR)/parse_scene.c \
	  $(PARSER_DIR)/parse_objects.c \
	  $(PARSER_DIR)/parse_values.c \
