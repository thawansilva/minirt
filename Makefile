include config.mk

# Source files and Objects
SRC := $(SRC:%=$(SRC_DIR)/%)
SRC_BONUS := $(SRC_BONUS:%=$(SRC_BONUS_DIR)/%)
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS := $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Libs
LIBS := ft mlx m Xext X11
LIBS_TARGET := lib/libft/libft.a lib/minilibx-linux/libmlx.a

# Flags
CC := cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS := $(addprefix -I, $(INC_DIR))
CPPFLAGS_BONUS := $(addprefix -I, $(INC_BONUS_DIR))
LDFLAGS := $(addprefix -L, $(dir $(LIBS_TARGET)))
LDLIBS := $(addprefix -l, $(LIBS))

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g2 -O0
endif

RM := rm -f
RMDIR := rm -fr
DUP_DIR = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBS_TARGET)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME_BONUS)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS_BONUS) -c $< -o $@

valgrind-run:
	@valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--trace-children=yes \
		--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
		./$(NAME) $(INPUT)

clean:
	$(RMDIR) $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	make -C lib/libft/ fclean
	$(RM) lib/minilibx-linux/libmlx.a
	$(RM) $(NAME) $(NAME_BONUS)

test:
	make -C tests run

re: fclean all

# Check for development tools
check-tools:
	@echo "[INFO] Checking for development tools..."
	@command -v c_formatter_42 >/dev/null 2>&1 || { \
        echo "[WARNING] c_formatter_42 not found"; \
        echo "[INFO] Install with: pip3 install --user 42-formatter"; \
        echo ""; \
    }
	@command -v norminette >/dev/null 2>&1 || { \
        echo "[WARNING] norminette not found"; \
        echo "[INFO] Install with: pip3 install --user norminette"; \
        echo ""; \
    }
	@if command -v c_formatter_42 >/dev/null 2>&1 && command -v norminette >/dev/null 2>&1; then \
        echo "[OK] All development tools are installed"; \
    else \
        echo "[INFO] Some tools are missing. Install them for full functionality."; \
    fi

# Git hooks setup
setup: check-tools
	@bash scripts/setup-hooks.sh

.PHONY: all clean fclean re bonus setup check-tools
