

SRCS = home/*.c

NAME = minishell
INCLUDE = inc/
FLAGS = -Werror -Wextra -Wall
GCC = gcc $(FLAGS) -I $(INCLUDE)

LIB_PATH = libft/
LIB_FLAGS = -L $(LIB_PATH) -lft
LIB1 = libft.a

RM = rm -f

$(NAME):
	make -C $(LIB_PATH)
	$(GCC) $(LIB_FLAGS) $(SRCS) -o $(NAME)

all:		$(NAME)

clean:
	make clean -C $(LIB_PATH)

fclean:		clean
	make fclean -C $(LIB_PATH)
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
