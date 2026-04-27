ROOT_DIR ?= ..

include $(ROOT_DIR)/config.mk

INC_MINIRT = inc

LIBFT_DIR := lib/libft
CFLAGS += -g2 -O0

LIBFT_PATH := $(ROOT_DIR)/$(LIBFT_DIR)
SRC_PATH := $(ROOT_DIR)/$(SRC_DIR)
SRC_BONUS_PATH := $(ROOT_DIR)/$(SRC_BONUS_DIR)
LIBFT_LIB := $(LIBFT_PATH)/libft.a
INCLUDES = -I$(ROOT_DIR)/$(INC_MINIRT) -I$(LIBFT_PATH)/inc

TEST_OBJ_DIR = obj
TEST_OBJ_BONUS_DIR = obj_bonus
TEST_INC_DIR = inc
TEST_INC_BONUS_DIR = inc_bonus
TEST_BONUS_DIR = bonus
TEST_VALIDATION_DIR = validation
TEST_PARSER_DIR = parser

# CMocka
CMOCKA_DIR = $(ROOT_DIR)/lib/cmocka
CMOCKA_BUILD = $(CMOCKA_DIR)/build
CMOCKA_INCLUDE = $(CMOCKA_DIR)/include
CMOCKA_LIB = $(CMOCKA_BUILD)/src/libcmocka.a
CMOCKA_VERSION = 1.1.7

INCLUDES += -I$(CMOCKA_INCLUDE) -I$(TEST_INC_DIR)
INCLUDES_BONUS = -I$(CMOCKA_INCLUDE) -I$(TEST_INC_BONUS_DIR) \
				 -I$(ROOT_DIR)/inc_bonus -I$(LIBFT_PATH)/inc

# Mandatory tests
TEST_FILES = test_main.c \
			 $(TEST_VALIDATION_DIR)/test_validation.c \
			 $(TEST_PARSER_DIR)/test_parser.c \
			 $(TEST_PARSER_DIR)/test_parse_elements.c

TEST_OBJ = $(TEST_FILES:%.c=$(TEST_OBJ_DIR)/%.o)
TEST_BIN = run_tests

PROJECT_OBJ = $(SRC:%.c=$(TEST_OBJ_DIR)/project/%.o)
PROJECT_OBJ := $(filter-out $(TEST_OBJ_DIR)/project/main.o, $(PROJECT_OBJ))

# Bonus tests
BONUS_TEST_FILES = test_bonus_main.c \
				   $(TEST_BONUS_DIR)/test_validation_bonus.c \
				   $(TEST_BONUS_DIR)/test_parser_bonus.c \
				   $(TEST_BONUS_DIR)/test_parse_elements_integration.c

BONUS_TEST_OBJ = $(BONUS_TEST_FILES:%.c=$(TEST_OBJ_BONUS_DIR)/%.o)
BONUS_TEST_BIN = run_tests_bonus

PROJECT_OBJ_BONUS = $(SRC_BONUS:%.c=$(TEST_OBJ_BONUS_DIR)/project/%.o)
PROJECT_OBJ_BONUS := $(filter-out $(TEST_OBJ_BONUS_DIR)/project/main_bonus.o, $(PROJECT_OBJ_BONUS))

TEST_LIBS = -L$(CMOCKA_BUILD)/src -lcmocka -L$(LIBFT_PATH) -lft -lm

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: mandatory bonus

mandatory: $(TEST_BIN)

bonus: $(BONUS_TEST_BIN)

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

# Mandatory test compilation rules
$(TEST_OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_OBJ_DIR)/project/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_BIN): $(CMOCKA_LIB) $(LIBFT_LIB) $(TEST_OBJ) $(PROJECT_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(PROJECT_OBJ) $(TEST_LIBS) -o $(TEST_BIN)
	@echo "$(GREEN)[OK] Tests compiled$(RESET)"

# Bonus test compilation rules
$(TEST_OBJ_BONUS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

$(TEST_OBJ_BONUS_DIR)/project/%.o: $(SRC_BONUS_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

$(BONUS_TEST_BIN): $(CMOCKA_LIB) $(LIBFT_LIB) $(BONUS_TEST_OBJ) $(PROJECT_OBJ_BONUS)
	$(CC) $(CFLAGS) $(BONUS_TEST_OBJ) $(PROJECT_OBJ_BONUS) $(TEST_LIBS) -o $(BONUS_TEST_BIN)
	@echo "$(GREEN)[OK] Bonus tests compiled$(RESET)"


# Test execution targets - Mandatory
run: mandatory
	@./$(TEST_BIN)

run-single: mandatory
	@./$(TEST_BIN) $(TEST)

# Test execution targets - Bonus
run-bonus: bonus
	@./$(BONUS_TEST_BIN)

run-bonus-single: bonus
	@./$(BONUS_TEST_BIN) $(TEST)

# Valgrind targets - Mandatory
valgrind: mandatory
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(TEST_BIN)

valgrind-single: mandatory
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(TEST_BIN) $(TEST)

valgrind-log: mandatory
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 --log-file=valgrind.out ./$(TEST_BIN)

valgrind-ci: mandatory
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 ./$(TEST_BIN)

# Valgrind targets - Bonus
valgrind-bonus: bonus
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(BONUS_TEST_BIN)

valgrind-bonus-single: bonus
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(BONUS_TEST_BIN) $(TEST)

valgrind-bonus-log: bonus
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 --log-file=valgrind_bonus.out ./$(BONUS_TEST_BIN)

valgrind-bonus-ci: bonus
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --errors-for-leak-kinds=definite,indirect --error-exitcode=1 ./$(BONUS_TEST_BIN)

# Filter targets
filter: mandatory
	@CMOCKA_TEST_FILTER="$(FILTER)" ./$(TEST_BIN)

filter-bonus: bonus
	@CMOCKA_TEST_FILTER="$(FILTER)" ./$(BONUS_TEST_BIN)

help:
	@echo "$(YELLOW)Minirt Test Makefile$(RESET)"
	@echo ""
	@echo "$(YELLOW)Main Targets:$(RESET)"
	@echo "  make              Build mandatory and bonus tests"
	@echo "  make mandatory    Build mandatory tests"
	@echo "  make bonus        Build bonus tests"
	@echo ""
	@echo "$(YELLOW)Mandatory Test Targets:$(RESET)"
	@echo "  make run          Run mandatory tests"
	@echo "  make run-single TEST=<name>  Run specific test group"
	@echo "  make valgrind     Run mandatory tests with Valgrind"
	@echo "  make valgrind-single TEST=<name>  Run specific test with Valgrind"
	@echo "  make filter FILTER='*pattern*' Run matching mandatory tests"
	@echo ""
	@echo "$(YELLOW)Bonus Test Targets:$(RESET)"
	@echo "  make run-bonus    Run bonus tests"
	@echo "  make run-bonus-single TEST=<name>  Run specific bonus test"
	@echo "  make valgrind-bonus     Run bonus tests with Valgrind"
	@echo "  make valgrind-bonus-single TEST=<name>  Run specific bonus test with Valgrind"
	@echo "  make filter-bonus FILTER='*pattern*' Run matching bonus tests"
	@echo ""
	@echo "$(YELLOW)Cleanup:$(RESET)"
	@echo "  make clean       Remove object files"
	@echo "  make fclean      Remove all generated files"
	@echo "  make re          Clean and rebuild"

clean:
	@rm -rf $(TEST_OBJ_DIR) $(TEST_OBJ_BONUS_DIR)
	@echo "$(GREEN)[OK] Test objects removed$(RESET)"

fclean: clean
	@rm -f $(TEST_BIN) $(BONUS_TEST_BIN)
	@echo "$(GREEN)[OK] Test files removed$(RESET)"

re: fclean all

.PHONY: all mandatory bonus run run-single run-bonus run-bonus-single \
		valgrind valgrind-single valgrind-log valgrind-ci \
		valgrind-bonus valgrind-bonus-single valgrind-bonus-log valgrind-bonus-ci \
		filter filter-bonus help clean fclean re

