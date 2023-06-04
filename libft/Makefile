# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 08:59:19 by samjaabo          #+#    #+#              #
#    Updated: 2022/10/31 17:21:44 by samjaabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c \
		ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_bzero.c ft_strchr.c ft_strrchr.c ft_strlen.c ft_strnstr.c \
		ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_atoi.c \
		ft_itoa.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c

OBJS =	$(SRCS:%.c=%.o)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: clean all

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) -Wall -Wextra -Werror -c $<
