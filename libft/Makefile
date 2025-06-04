# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 12:08:57 by tiaperei          #+#    #+#              #
#    Updated: 2025/06/04 17:32:15 by lgirerd          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -I./include -I../include

GREEN  			= \033[1;32m
RESET  			= \033[0m

SRCS_DIR = srcs/
SOURCES_FILES = 	ft_atoi.c \
					ft_atoll.c \
					ft_itoa.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_lstadd_back_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstnew_bonus.c \
					ft_lstsize_bonus.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c	\
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_printf.c \
					print_char.c \
					print_number.c \
					print_pointer.c \
					print_string.c \
					print_unsigned.c \
					ft_strcmp.c \

SOURCES = $(addprefix $(SRCS_DIR), $(SOURCES_FILES))

OBJECTS = $(SOURCES:.c=.o)

DEPENDS = $(OBJECTS:.o=.d)
TOTAL   = $(words $(SOURCES))

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar -rcs $@ $^
	@printf "\n"

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c
	@INDEX=$$(echo "$(SOURCES)" | tr ' ' '\n' | grep -n "$<" | cut -d: -f1); \
	PERCENT=$$((INDEX * 100 / $(TOTAL))); \
	BAR=$$(printf "#%.0s" $$(seq 1 $$((PERCENT / 2)))); \
	SPACES=$$(printf " %.0s" $$(seq 1 $$((50 - PERCENT / 2)))); \
	printf "\r$(GREEN)libft: [$$BAR$$SPACES] $$INDEX/$(TOTAL)$(RESET)"; \
	$(CC) $(CFLAGS) -MMD -c $< -o $@; \
	
-include $(DEPENDS)
	
clean:
	@rm -f $(OBJECTS) $(DEPENDS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
