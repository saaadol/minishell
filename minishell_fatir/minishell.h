/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:50:06 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 15:29:51 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_gcl_ptf/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include<sys/time.h>
# include <readline/history.h>

# define WORD 1
# define SEP 2

typedef struct s_env{
	char			*cmd;
	char			*str;
	int				v;
	struct s_env	*next;
}	t_env;
typedef struct s_list{
	char			*str;
	int				type;
	struct s_list	*next;
}	t_list;
typedef struct s_var{
	char		*c;
	char		*f;
	char		*str;
	int			j;
	int			k;
	int			b;
}	t_var;

//linked_list.c
t_list	*ft_cr_list(char *cmd);
void	ft_add_end(t_list **a, t_list *n);
int		ft_strlen_stack(t_list **a);
void	free_list(t_list *list, char *cmd);
//separators.c
char	*ft_strndup(char *str, int start, int end);
int		get_index(int i, char *cmd);
int		handle_quote(t_list **arg, char *cmd, int i);
int		handle_sep(t_list **arg, char *cmd, int i);
int		is_char(t_list **arg, char *cmd, int i);
// quotes.c
int		quote_num(char *cmd, int flag);
char	*resize(char *cmd, int i, int b);
void	quote_rm(t_list **arg);
int		first_qoute(char *str);
int		check_nodes(t_list *arg);
//utils.c
void	print_nodes(t_list *arg);
int		not_sep(char c);
int		is_sep(char c, int x);
char	*dupping(char *str, char *p);
// parcing.c
// void	token_to(char *cmd, t_list **arg); original
int	token( char **env,  char *cmd, t_list *arg, t_env	*envs); //temp
// int		token(char *cmd, t_list *arg, t_env	*envs); original
// void	parsing(,t_list *arg, char **env); //original
void	parsing(t_list *arg, char **env);
//env.c
t_env	*get_env(char **env, t_env *envs);
void	free_listt(t_env *list);
t_env	*ft_cr_listt(char *cmd, char *str, int i);
void	ft_add_endd(t_env **a, t_env *n);
// expanding.c
char	*expander(char *cmd, t_env **env);
void	expanding(t_list **arg, t_env **envs);
// expanding2.c
char	*ft_free_expand(t_var *v);
char	*get_env_str(char *cmd, t_env **env);
int		get_expande(char *cmd, int i, t_env **env, t_var *v);
int		sep_case(char *cmd, int i, t_var *v, t_env **env);
int		else_case(char *cmd, int i, t_var *v, t_env **env);
// check_syntax.c
int		check_sep_valid(char *str, char *next);
int		check_syntax(t_list **arg);
// export.c
void	expo_exist_norm(char *str, t_env **env, int i);
int		export(t_list **args, t_env **envs);
int		export_valid(char *arg, t_env **envs);
int		expo_exist(char *arg, int i, t_env **envs);
// export2.c
void	print_env(t_env *arg);
void	print_env_xp(t_env *arg);
int		is_valide(char *arg);
int		ft_export(char *arg, t_env **envs);
//execution
int  heredoc_(int ac, char **av, char *envp[], char *delimiter);
char	*checking_path(char *envp[], char *comm);
void	while_pipe(int **pips);
char	*ft_newstrchr(char *s, char *target);
int sep_len(t_list **arg);
void	exec_function(char *envp[], char **command, char *x);
pid_t	bonus_child_fork_1(t_list **arg, char *envp[], int **array, char *command, int fd_, int infile, int outfile);
int	**handling_multiple_pipes(t_list **arg);
void checking_if_pipe_exists(char **envp, int **array,  t_list **argv);
#endif