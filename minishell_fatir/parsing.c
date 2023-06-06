/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:55:03 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 15:30:24 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_to(char *cmd, t_list **arg)
{
	int		i;
	int		k;

	i = 0;
	k = ft_strlen(cmd);
	while (i < k)
	{
		if (cmd[i] && is_sep(cmd[i], 3))
			i++;
		if (cmd[i] && is_sep(cmd[i], 1))
			i = handle_sep(arg, cmd, i);
		if (cmd[i] && is_sep(cmd[i], 2))
			i = handle_quote(arg, cmd, i);
		if (cmd[i] && not_sep(cmd[i]))
			i = is_char(arg, cmd, i);
	}
}

int	token(char **env, char *cmd, t_list *arg, t_env	*envs)
{
	int		i;
	int		**array;
	// printf("%s", env[2]);
	// exit(1);
	cmd = ft_strtrim(cmd, " ");
	arg = NULL;
	token_to(cmd, &arg);
	expanding(&arg, &envs);
	if (!check_nodes(arg) || !check_syntax(&arg))
		return (free_list(arg, cmd), 0);
	quote_rm(&arg);
	if (!export(&arg, &envs))
		ft_putstr_fd("\033[1;31mminishell$: not a valid identifier\033[0m\n", 2);

	array = handling_multiple_pipes(&arg);
	i = 0;
	
	while (i < sep_len(&arg))
	{
		if (pipe(array[i++]) == -1)
			exit(1);
	}

	// while (arg)
	// {
	// 	printf("%d\n", arg->type);
	// 	arg = arg->next;
	// }
	checking_if_pipe_exists(env, array, &arg);
	//exit(1);



	free_list(arg, cmd);
	return (1);

}





	
	//print_nodes(arg);

void	parsing(t_list *arg, char **env)
{	
	char	*cmd;
	t_env	*envs;

	envs = NULL;
	//envs = get_env(env, envs);

	while (1)
	{
		cmd = readline("\033[1;34mminishell$\033[0m ");
		if (!ft_strcmp(cmd, "exit"))
		{
			free(cmd);
			break ;
		}
		add_history(cmd);
		if (!token(env, cmd, arg, envs))
			ft_putstr_fd("\033[1;31mminishell$: syntax error\033[0m\n", 2);
		
		free(cmd);
		
		// printf("lol");
		
	}
	free_listt(envs);
	clear_history();
}



// int	main(int ac, char **av, char **env)
// {
// 	t_list	arg;

	
// 	(void)ac;
// 	(void)av;
// 	parsing(&arg, env);
// 	//printf("lol");
// 	return (0);
// }


int	main(int ac, char **av, char **env)
{
	t_list	arg;


	parsing(&arg, env);
	
	
	
 
	// closing_pipes(ac, array);
	//waitpid(fn, NULL, 0);
	
	return (0);
}
