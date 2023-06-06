# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 09:48:54 by afatir            #+#    #+#              #
#    Updated: 2023/06/05 15:12:52 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CFLAGS	= -fsanitize=address#-Wall -Werror -Wextra 
CC		= cc
LIB_FT	= ./libft_gcl_ptf/
LIB_FT_A= ./libft_gcl_ptf/libft_gcl_ptf.a
MOBJS	= ${SRCS:%.c=%.o}
SRCS	= parsing.c separators.c quotes.c linked_list.c utils.c env.c \
			expanding.c expanding2.c check_syntax.c export.c export2.c \
			../minishell.c  ../util_functions.c ../executin_multiple_pipes.c \
			../execution.c

all : $(NAME)
	@make -C $(LIB_FT)

$(NAME) : $(MOBJS)
	@make -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(LIB_FT_A) $(MOBJS) -o $(NAME) -lreadline
# @make clean

%.o: %.c minishell.h
	$(CC) $(CFLAGS)  -c $< -o $@
clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS) 

fclean:	clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)

re:	fclean all