# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 17:00:03 by lgirerd           #+#    #+#              #
#    Updated: 2025/03/26 19:54:53 by lgirerd          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    		= pipex
CC      		= cc
CFLAGS  		= -Wall -Wextra -Werror
LIBFT			= ./libft/libft.a
INC				= -I$(LIBFT_HDR_DIR) -I$(HDR_DIR)
HDR				= pipex.h
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
SRCS    	= $(SRCS_DIR)pipex.c \
			  $(SRCS_DIR)utils.c \
			  $(SRCS_DIR)errors.c \
			  $(SRCS_DIR)execute.c

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
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compilation successful! 🎉$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(addprefix $(HDR_DIR)/, $(HDR))
	@mkdir -p $(OBJS_DIR)
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

-include $(DEPS)

.PHONY: all clean fclean re norm
