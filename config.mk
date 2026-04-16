NAME = miniRT
NAME_BONUS = miniRT_bonus

INC_DIR = inc lib/libft/inc/ lib/minilibx-linux/
SRC_DIR = src
OBJ_DIR = obj
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

VALIDATION_DIR = validation

SRC = main.c \
	  free_memory.c \
	  $(VALIDATION_DIR)/input.c \
	  $(VALIDATION_DIR)/validate_objects.c \
	  $(VALIDATION_DIR)/validate_scene.c \
	  $(VALIDATION_DIR)/validate_properties.c \
	  $(VALIDATION_DIR)/validate_number_values.c \
