#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <readline/history.h>
#include <dirent.h>
#include <sys/types.h>
# include <fcntl.h>



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
void	executing_funcs(int ac, char **av, char *envp[]);
void exec_command(char *envp[], char **command, char *x, int ac, char **av);
pid_t child_fork_heredoc_1(int ac, char **av, char *envp[], int **pips);
pid_t child_fork_heredoc_2(int ac, char **av, char *envp[], int **pips);
void freeying_pips(int **pips);
void	executing_func(int ac,char **av, char *envp[], int **pips);
void heredoc_(int ac, char **av, char *envp[]);
char	*checking_path(char *envp[], char *comm);
void	while_pipe(int **pips);
char	*ft_newstrchr(char *s, char *target);
int sep_len(char **str);
void	exec_function(char *envp[], char **command, char *x);
pid_t	bonus_child_fork_1(int ac, char **av, char *envp[], int **array, char *command, int fd_, int infile);


#endif