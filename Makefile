# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 16:14:57 by swagstaf          #+#    #+#              #
#    Updated: 2021/04/16 16:01:31 by swagstaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

HEADER =	includes/*.h
LIBFT =		libft
LFLAGS =	-L $(LIBFT) -lft -ltermcap
FLAGS =		-Wall -Werror -Wextra
ALL_INC =	-I includes/ -I $(LIBFT)

SRC_DIR =	srcs/

CFILE =		minishell.c \
			utils_1.c \
			utils_2.c \
			ft_parse.c \
			ft_pwd.c \
			ft_echo.c \

LIB_F =		$(LIBFT)/*.c

OFILE =		$(CFILE:.c=.o)

SRC =		$(addprefix $(SRC_DIR), $(OFILE))
OBJ =		$(addprefix $(SRC_DIR), $(OFILE))

all: $(NAME)

$(OBJ) : $(HEADER)

$(NAME): $(LIBFT)/libft.h $(LIB_F) $(OBJ)
		@make -C $(LIBFT)
		gcc $(FLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

%.o : %.c
		gcc $(FLAGS) $(ALL_INC) -c $< -o $@

clean:
		@make clean -C $(LIBFT)
		@/bin/rm -f $(OBJ)
		@echo Cleaned $(NAME) object files

fclean: clean
		@make fclean -C $(LIBFT)
		@/bin/rm -f $(NAME)
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean flcean re
