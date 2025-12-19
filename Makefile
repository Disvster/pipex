SHELL :=/bin/bash

# pipex
SRC_DIR = src/
SRC =	exec_commands.c \
		main.c \
		parse_commands.c \
		pipe.c \
		utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR),$(notdir $(SRCS:.c=.o)))

# LIBFT
LIBFT = libft/libft.a
LIBFT_DIR = libft/

# PROGRESS BAR
TOTAL_C := $(shell find src/ -type f -name '*.c' -not -path '*/.*' | wc -l)

define	progress_bar
	@COUNT=$$(find obj -type f -name '*.o' | wc -l); \
	BAR_WIDTH=30; \
	NUM_HASHES=$$(( COUNT * BAR_WIDTH / $(TOTAL_C) )); \
	BAR=$$(printf "%-$${BAR_WIDTH}s" "$$(printf '%0.s#' $$(seq 1 $$NUM_HASHES))"); \
	echo -ne "Compiling: [$$BAR] ($$COUNT/$(TOTAL_C))\r"
endef

INCS_DIR = incs/
CC = cc
CFLAGS = -Wall -Werror -Wextra -g 
NAME = pipex
RM = rm -f

all: $(OBJ_DIR) $(LIBFT) $(NAME)
	@echo -e "Compilation complete! pipex file generated.                         \n"

print_pipex:
	@echo -e "\n======  pipex  ======"

print_libft:
	@echo -e "\n=====  Libft  ====="

$(OBJ_DIR):
	@mkdir $@

$(LIBFT): print_libft
	@make --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)
	$(progress_bar)

$(NAME): print_pipex $(LIBFT) $(LIBX) $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBX) $(L_CFLAGS) -o $(NAME)

clean: $(OBJ_DIR)
	@make --no-print-directory print_libft
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory print_pipex
	@$(RM) -r $(OBJ_DIR)
	@echo -e "cleaned .o files\n"

fclean: $(OBJ_DIR)
	@make --no-print-directory print_libft
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@make --no-print-directory print_pipex
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned .o files"
	@$(RM) $(NAME)
	@echo -e "Cleaned pipex executable\n"

re: fclean $(OBJ_DIR)
	@make --no-print-directory all

.PHONY: all clean fclean re print_pipex print_libft
