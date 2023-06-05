# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 08:59:19 by samjaabo          #+#    #+#              #
#    Updated: 2023/06/04 18:02:09 by moouaamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = objs/program.a
CC = cc
CFLAGS = -fsanitize=address # -Wall -Wextra -Werror
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -lm

# directory variables
LIBFT_DIR = ./libft/
OBJS_DIR = ./objs/

MAIN_SRC = main.c utils.c get_next_line_utils.c get_next_line.c map.c mlx_widget.c
#src files
LIBFT_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c \
		ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_bzero.c ft_strrchr.c ft_strnstr.c \
		ft_strlcpy.c ft_strlcat.c ft_strncmp.c \
		ft_itoa.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strtrim.c ft_split.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_atoi.c



#src files with path
LIBFT_SRCS = $(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

# object files variables
MAIN_OBJS = $(addprefix $(OBJS_DIR),$(MAIN_SRC:.c=.o))
LIBFT_OBJS =	$(LIBFT_SRCS:%.c=%.o)

all: $(NAME) run


clean:
	@rm -rf $(LIBFT_OBJS) $(MAIN_OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

$(NAME): $(LIBFT_OBJS) $(MAIN_OBJS)
	@ar rc $(NAME) $(LIBFT_OBJS) $(MAIN_OBJS)
	@$(CC) $(CFLAGS) $(NAME) -o objs/program $(MLXFLAGS)

objs/%.o: %.c header.h ./libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@#clear
	@objs/program maps/map3.cub
