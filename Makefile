# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 17:00:03 by lgirerd           #+#    #+#              #
#    Updated: 2025/05/01 17:29:06 by lgirerd          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    		= minishell
CC      		= cc
CFLAGS  		= -Wall -Wextra -Werror -g3
LIBFT			= ./libft/libft.a
INC				= -I$(LIBFT_HDR_DIR) -I$(HDR_DIR)
HDR				= cmd.h builtins.h errors.h colors.h minishell.h parsing.h signals.h utils.h pipes.h
HDR_DIR			= include
LIBFT_HDR_DIR	= libft/include
LIBFT_HDR		= libft.h
GREEN			= \033[1;32m
RESET			= \033[0m
RED				= \033[0;31m
BLUE			= \033[34m
YELLOW			= \033[0;33m


############################# SOURCES #############################

SRCS_DIR 	= srcs/
SRCS    	=	$(SRCS_DIR)minishell.c \
				$(SRCS_DIR)init_parsing.c \
				$(SRCS_DIR)export.c \
				$(SRCS_DIR)expand.c \
				$(SRCS_DIR)expand_size.c \
				$(SRCS_DIR)command.c \
				$(SRCS_DIR)free_data.c \
				$(SRCS_DIR)signals.c \
				$(SRCS_DIR)utils.c \
				$(SRCS_DIR)echo.c \
				$(SRCS_DIR)free_utils.c \
				$(SRCS_DIR)cd.c \
				$(SRCS_DIR)errors.c \
				$(SRCS_DIR)exit.c \
				$(SRCS_DIR)pwd.c \
				$(SRCS_DIR)env.c \
				$(SRCS_DIR)export_utils.c \
				$(SRCS_DIR)export.c \
				$(SRCS_DIR)unset.c \
				$(SRCS_DIR)print_export.c \
				$(SRCS_DIR)builtins.c \
				$(SRCS_DIR)cmd.c \
				$(SRCS_DIR)open_files.c \
				$(SRCS_DIR)executer.c \
				$(SRCS_DIR)pipeline.c \
				$(SRCS_DIR)pipes_utils.c \

############################# DIRECTORIES ##############################

OBJS_DIR = .objs/
OBJS    = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS := $(OBJS:.o=.d)

############################# RULES ##############################

all: $(LIBFT) $(NAME)

$(LIBFT): force $(LIBFT_HDR_DIR)/$(LIBFT_HDR)
	@make --no-print-directory -C ./libft

force:
$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compilation successful! 🎉$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(addprefix $(HDR_DIR)/, $(HDR))
	@mkdir -p  $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@
	@echo "$(BLUE)Compiling : $< 🔧$(RESET)"
	
clean:
	@make --no-print-directory clean -C libft
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Cleaned project 🗑️$(RESET)"

fclean:
	@make --no-print-directory fclean -C libft
	@rm -rf $(NAME) && rm -rf $(OBJS_DIR)
	@echo "$(RED)Fully cleaned project 🗑️$(RESET)"
	
re: fclean all

norm:
	@norminette srcs || true
	@norminette include || true
	@norminette libft | grep Error || true 

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--show-mismatched-frees=yes --trace-children=yes \
	--suppressions=rl_leaks.supp ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re norm val
