#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <readline/history.h>
#include <dirent.h>




typedef struct t_list{
	char			*string;
	struct t_list	*next;
}	t_list;


void adding_node(t_list **arg);
char *ft_strndup(char *str, int start, int end);
char	**ft_split(char const *s, char c);
int is_alpha_numeric(char x);
int is_white_space(char x);
int is_quote(char x);
int is_separator(char x);
char *ft_strtrim(char  *word, char  *delimiter);
char    *ft_strcpy(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, size_t n);
void print_nodes(t_list *arg);
int is_special_char(char x);

#endif