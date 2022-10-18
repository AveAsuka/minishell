# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:22:15 by lbrianna          #+#    #+#              #
#    Updated: 2022/08/03 14:51:38 by lbrianna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a
SRCS = 		ft_isalpha.c		ft_isdigit.c	ft_isalnum.c\
	   		ft_isascii.c		ft_isprint.c	ft_strlen.c\
	   		ft_memset.c		ft_bzero.c		ft_memcpy.c\
	   		ft_memmove.c		ft_strlcpy.c	ft_strlcat.c\
	   		ft_toupper.c		ft_tolower.c	ft_strchr.c\
	   		ft_strrchr.c		ft_strncmp.c	ft_memchr.c\
	   		ft_memcmp.c		ft_strnstr.c	ft_atoi.c\
	   		ft_calloc.c		ft_strdup.c\
	   		ft_substr.c	  	ft_strjoin.c	ft_strtrim.c\
	   		ft_split.c		ft_itoa.c		ft_strmapi.c\
	   		ft_striteri.c	ft_putchar_fd.c	ft_putstr_fd.c\
	   		ft_putendl_fd.c	ft_putnbr_fd.c 

BONUS =		ft_lstnew_bonus.c	ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c	ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c	ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c		ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\

CC = 		gcc
HEADER =	libft.h
INCLUDES = 	../../includes
RM = 		rm -f
CFLAGS = 	-Wall -Wextra -Werror -g
OBJS = 		$(SRCS:.c=.o)

OBJSB = 	$(BONUS:.c=.o)

all: 		$(NAME)


$(NAME) : 	$(OBJS) $(HEADER)
	ar rcs $(NAME) $?

bonus :
	make OBJS="$(OBJSB)" all

%.o : %.c $(INCLUDES)$(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)
	
clean: 
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(RM) $(NAME) $(OBJSB) 

re: fclean $(NAME)

.PHONY: all clean fclean re bonus
