ROOT_DIR ?= ..

include $(ROOT_DIR)/config.mk

INC_MINIRT = inc

LIBFT_DIR := lib/libft
CFLAGS += -g2 -O0

LIBFT_PATH := $(ROOT_DIR)/$(LIBFT_DIR)
SRC_PATH := $(ROOT_DIR)/$(SRC_DIR)
LIBFT_LIB := $(LIBFT_PATH)/libft.a
INCLUDES = -I$(ROOT_DIR)/$(INC_MINIRT) -I$(LIBFT_PATH)/inc

TEST_OBJ_DIR = obj
TEST_INC_DIR = inc
TEST_VALIDATION_DIR = validation

# CMocka
CMOCKA_DIR = $(ROOT_DIR)/lib/cmocka
CMOCKA_BUILD = $(CMOCKA_DIR)/build
CMOCKA_INCLUDE = $(CMOCKA_DIR)/include
CMOCKA_LIB = $(CMOCKA_BUILD)/src/libcmocka.a
CMOCKA_VERSION = 1.1.7

INCLUDES += -I$(CMOCKA_INCLUDE) -I$(TEST_INC_DIR)

TEST_FILES = test_main.c \
			 $(TEST_VALIDATION_DIR)/test_validation.c

TEST_OBJ = $(TEST_FILES:%.c=$(TEST_OBJ_DIR)/%.o)
TEST_BIN = run_tests

PROJECT_OBJ = $(SRC:%.c=$(TEST_OBJ_DIR)/project/%.o)
PROJECT_OBJ := $(filter-out $(TEST_OBJ_DIR)/project/main.o, $(PROJECT_OBJ))

TEST_LIBS = -L$(CMOCKA_BUILD)/src -lcmocka -L$(LIBFT_PATH) -lft

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(TEST_BIN)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH) DEBUG=1

$(CMOCKA_LIB):
	@if [ -f "$(CMOCKA_LIB)" ]; then \
        echo "$(GREEN)[OK] CMocka already installed$(RESET)"; \
    else \
        echo "$(YELLOW)[INFO] Installing CMocka...$(RESET)"; \
        if [ ! -d "$(CMOCKA_DIR)" ]; then \
            curl -L https://cmocka.org/files/1.1/cmocka-$(CMOCKA_VERSION).tar.xz -o /tmp/cmocka.tar.xz && \
            tar -xf /tmp/cmocka.tar.xz -C $(ROOT_DIR) && \
            mv $(ROOT_DIR)/cmocka-$(CMOCKA_VERSION) $(CMOCKA_DIR) && \
            rm /tmp/cmocka.tar.xz; \
        fi; \
        mkdir -p $(CMOCKA_BUILD) && \
        cd $(CMOCKA_BUILD) && \
        cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DWITH_STATIC_LIB=ON .. && \
        cmake --build . --config Debug; \
        echo "$(GREEN)[OK] CMocka built$(RESET)"; \
    fi

$(TEST_OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_OBJ_DIR)/project/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_BIN): $(CMOCKA_LIB) $(LIBFT_LIB) $(TEST_OBJ) $(PROJECT_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(PROJECT_OBJ) $(TEST_LIBS) -o $(TEST_BIN)
	@echo "$(GREEN)[OK] Tests compiled$(RESET)"

run: $(TEST_BIN)
	@./$(TEST_BIN)

run-single: $(TEST_BIN)
	@./$(TEST_BIN) $(TEST)

valgrind: $(TEST_BIN)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(TEST_BIN)

valgrind-single: $(TEST_BIN)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(TEST_BIN) $(TEST)

valgrind-log: $(TEST_BIN)
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 --log-file=valgrind.out ./$(TEST_BIN)

valgrind-ci: $(TEST_BIN)
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 ./$(TEST_BIN)

filter: $(TEST_BIN)
	@CMOCKA_TEST_FILTER="$(FILTER)" ./$(TEST_BIN)

help:
	@echo "$(YELLOW)Minishell Test Makefile$(RESET)"
	@echo ""
	@echo "make              Build tests"
	@echo "make run          Run all tests"
	@echo "make run-single TEST=lexer  Run specific group"
	@echo "make valgrind     Run with Valgrind"
	@echo "make filter FILTER='*echo*' Run matching tests"

clean:
	@rm -rf $(TEST_OBJ_DIR)
	@echo "$(GREEN)[OK] Test objects removed$(RESET)"

fclean: clean
	@rm -f $(TEST_BIN)
	@echo "$(GREEN)[OK] Test files removed$(RESET)"

re: fclean all

.PHONY: all run run-single valgrind valgrind-single valgrind-ci filter help debug clean fclean re

