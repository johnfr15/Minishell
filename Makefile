CC = gcc
SRC = $(addprefix ./src/, main.c init.c history.c error.c utils.c) \
	  $(addprefix ./src/parser/, lexer.c parser.c parse1.c parse2.c) \
	  $(addprefix ./src/executor/, exec.c) \
	  $(addprefix ./src/clear/, clear.c)
OBJ	= ${SRC:%.c=%.o}
LIBS = -L./libft/ -lft -lncurses
LIBFT = ./libft/
INCLUDE = -I./include -I./libft/includes 
CFLAGS = -Wall -Werror -Wextra
DEBUG = -fsanitize=address -g
NAME = minishell

all: ${NAME}

${NAME}: ${LIBFT} ${LIBMLX} ${OBJ}
	$(CC) $(DEBUG) $(LIBS) $(OBJ) -o $@

%.o: %.c
	${CC} -c $< ${CFLAGS} $(INCLUDE) -o ${<:%.c=%.o}

${LIBFT}:
	@echo "Compiling library libft"
	make -C ${LIBFT}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re ${LIBFT} ${LIBMLX}
