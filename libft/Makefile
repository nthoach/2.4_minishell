#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:32:48 by nthoach           #+#    #+#              #
#    Updated: 2024/04/25 17:50:51 by nthoach          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
SRC = free_double_ptr.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_printf.c \
	printf_c.c \
	printf_di.c \
	printf_p.c \
	printf_s.c \
	printf_u.c \
	printf_x.c \
	utils_blanks.c \
	utils_printf.c \
	utils_printfdi.c \
	utils_printfu.c \
	utils_sign.c \
	get_next_line.c \
	get_next_line_err.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	get_next_line_utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj
CFLAGS = -Wall -Werror -Wextra -g3
INCL = ./
CC = cc

$(NAME): $(OBJS) $(OBJ_DIR)
	ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f libft.a

re: fclean all

.PHONY: clean re fclean all