# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 12:08:57 by tiaperei          #+#    #+#              #
#    Updated: 2025/04/02 14:07:08 by tiaperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = $(wildcard ./srcs/*.c)

OBJECTS = $(SOURCES:.c=.o)

DEPENDS = $(OBJECTS:.o=.d)

CC = cc -I../include
CFLAGS = -Wall -Wextra -Werror -I./include -MMD

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
-include $(DEPENDS)
	
clean:
	rm -f $(OBJECTS) $(DEPENDS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
