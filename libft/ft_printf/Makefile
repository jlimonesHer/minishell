# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarriga <abarriga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 10:20:34 by jlimones          #+#    #+#              #
#    Updated: 2023/04/29 17:56:48 by abarriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c \
	  ft_check_type.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putnbr_int.c \
	  ft_putnbr_unsigned.c \
	  ft_p_nbr_hex.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

HEAD = libftprintf.h
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@ar crs $(NAME) $(OBJ)
	
%.o: %.c $(HEAD)
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re