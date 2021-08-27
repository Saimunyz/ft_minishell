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
			utils_3.c \
			./ft_parse/ft_parse.c \
			./ft_parse/ft_parse2.c \
			./ft_parse/ft_parse3.c \
			./ft_parse/ft_parse4.c \
			./ft_parse/ft_parse5.c \
			./ft_parse/ft_parse6.c \
			./ft_parse/ft_parse7.c \
			ft_pwd.c \
			ft_echo.c \
			ft_cd.c \
			ft_exit.c \
			ft_history.c \
			ft_signals.c \
			./ft_commands/ft_commands.c \
			ft_init.c \
			ft_env.c \
			ft_export.c \
			ft_unset.c \
			./ft_redirect/ft_redirect.c \
			./ft_redirect/ft_redirect2.c \
			ft_bubble_sort.c \
			ft_getenv.c \

LIB_F =		$(LIBFT)/*.c

OFILE =		$(CFILE:.c=.o)

SRC =		$(addprefix $(SRC_DIR), $(OFILE))
OBJ =		$(addprefix $(SRC_DIR), $(OFILE))

all: $(NAME)

$(OBJ) : $(HEADER)

$(NAME): $(LIBFT)/libft.h $(LIB_F) $(OBJ)
		@make -C $(LIBFT)
		gcc -g $(FLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

%.o : %.c
		gcc -g $(FLAGS) $(ALL_INC) -c $< -o $@

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
