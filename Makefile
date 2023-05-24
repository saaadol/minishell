NAME = minishell
FILES = minishell.c get_next_line.c get_next_line_utils.c function_utils.c util_functions.c

OBJ = $(FILES:.c=.o)
CC = cc
CFLAGS = -lreadline

all: $(NAME)

%.o : %.c get_next_line.h
	$(CC)   -c $< -o $@ 

$(NAME): $(OBJ) 
	${CC} $(CFLAGS) ${OBJ}  -o ${NAME}

clean :
	rm -rf $(OBJ) 
fclean : clean
	rm -rf $(NAME) 

re: fclean all
