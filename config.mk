NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
INC_DIR = inc
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./$(INC_DIR) -I$(LIBFT_DIR)/inc

EVAL_DIR = eval
HASHTABLE_DIR = hashtable
SRC_FILES = main.c \

BONUS_DIR = bonus
BONUS_OBJ_DIR = obj_bonus
