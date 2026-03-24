include config.mk

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g2 -O0
endif

OBJ_DIR = obj
SRC = $(SRC_FILES:%=$(SRC_DIR)/%)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBS = -lft

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIBS) -o $(NAME)
	@echo "[OK] $(NAME) compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(LIBFT) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT_DIR) $(LIBS) -o $(NAME)
	@echo "[OK] $(NAME) bonus compiled successfully"

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

valgrind-run:
	@valgrind -q\
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--trace-children=yes \
		--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
		--suppressions=./valgrind.supp \
		./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BONUS_OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "[OK] Object files removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "[OK] $(NAME) removed"

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
