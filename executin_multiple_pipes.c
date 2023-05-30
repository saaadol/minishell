/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executin_multiple_pipes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:17 by souledla          #+#    #+#             */
/*   Updated: 2023/05/30 11:16:40 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_error(void)
{
	perror("nice try ;D");
	exit(1);
}

void	exec_function(char *envp[], char **command, char *x)
{
	int	fd;

	fd = open(command[0], O_RDONLY, 0777);
	if (ft_strlen(x) == 0)
		print_error();
	if (fd < 0)
	{
		if (access(x, F_OK) == 0)
		{
			close(fd);
			if (execve(command[0], command, envp) == -1)
			{
				
				perror(x);
				exit(1);
			}	
		}
	}
	if (execve(checking_path(envp, command[0]), command, envp) == -1)
	{	
		close(fd);
		perror(x);
		exit(1);
	}
}

void	waiting_pid(pid_t f1, pid_t fn, pid_t f2)
{
	waitpid(f1, NULL, 0);
	waitpid(fn, NULL, 0);
	waitpid(f2, NULL, 0);
}


pid_t	bonus_child_fork_2(int *arr, char **av, char *envp[], int **array)
{
	pid_t	f2;
	int		fd2;
	int		i;
	char	**command;

	f2 = fork();
	if (f2 == 0)
	{
		fd2 = open(av[arr[0] -1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		command = ft_split(av[arr[0] - 2], ' ');
		dup2(fd2, 1);
		close(fd2);
		dup2(array[arr[1]][0], 0);
		i = 0;
		while (i < arr[0] - 4)
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		exec_function(envp, command, av[arr[0] - 2]);
	}
	return (f2);
}

int	while_loop_fork(int *arr, char **av, char *envp[], int **array, char *command)
{
	pid_t	fn;
	int		i;
	int j  = 0;
	char **splited_command = NULL;
	i = 0;
	
	while (i < sep_len(av))
	{
		fn = fork();
		if (fn == 0)
		{
			splited_command = ft_split(command, ' ');
			dup2(array[j][0], 0);
			dup2(array[j + 1][1], 1);
			while (i < sep_len(av))
			{
				close(array[i][0]);
				close(array[i][1]);
				i++;
			}
			exec_function(envp, splited_command, splited_command[0]);
		}
		j++;
	}
	return (fn);
}
void	closing_pipes(int ac, int **array)
{
	int	i;

	i = 0;
	while (i < ac - 2)
	{
		close(array[i][0]);
		close(array[i][1]);
		i++;
	}
}
pid_t	bonus_child_fork_1(int ac, char **av, char *envp[], int **array, char *command)
{
	pid_t	f1 = 0;
	int		fd1;
	// char	**command;
	char **splited_command;
	int		i;
	i = 0 ;
	int fd[2];
	splited_command = ft_split(command, ' ');
	while (splited_command[i])
	{
		i++;
	}
	
	if (i == 1)
	{
		execve(checking_path(envp, splited_command[0]), splited_command, envp);
		exec_function(envp, splited_command, splited_command[0]);
	}
	else
	
	{	
		f1 = fork();
		if (f1 == 0)
		{	
			// fd1 = open(av[1], O_RDONLY, 0777);
			// command = ft_split(av[2], ' ');
			// if (dup2(fd1, 0) == -1)
			// {
			// 	perror(av[1]);
			// 	exit(1);
			// }
			// close(fd1);
			if (dup2(array[0][1], 1) == -1)
				perror("Pipe:");
			// closing_pipes(ac, array);
			execve(checking_path(envp, splited_command[0]), splited_command, envp);
			exec_function(envp, splited_command, splited_command[0]);
		}
		
	}
	i = 0;
	while (array[i])
	{
		close(array[i][0]);
		close(array[i][1]);
		i++;
	}
	   
	waitpid(f1, NULL, 0);                                                                                                                                                                                                                                                                                      
	return (f1);
}

int	**handling_multiple_pipes(char **av)
{
	int	number_of_pipes;
	if (!sep_len(av))
		number_of_pipes = 1;
	else
		number_of_pipes = sep_len(av);
	int	**array_of_pipes;
	int	i;	

	i = 0;
	array_of_pipes = malloc(sizeof(int *) * (number_of_pipes));
	while (i < number_of_pipes)
	{
		array_of_pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (array_of_pipes);
}
void freeying_command_array(char **command)
{	
	if (!command)
        return;
	int i = 0;

	while (command[i])
	{
		free(command[i++]);
	}
	//free(command);
}
int sep_len(char **str)
{
	int i = 1;
	int counter = 0;
	while(str[i])
	{
		if (str[i][0] == '|' && ft_strlen(str[i]) == 1)
		{
			counter++;
		}	
		i++;
	}
	return counter; 
}

int calcul_arg(char **str)
{
	
	static int i = 1;
	int counter = 0;
	while(str[i])
	{	
		if (str[i][0] == '|' && ft_strlen(str[i]) != 1)
		{
			i++;
			return counter;	
		}
		counter++;
		i++;
	}
	return counter; 
}


void checking_if_pipe_exists(int ac, char **av, char **envp, int **array, int *arr)
{
	char *command = NULL;
	
	char *joined = NULL;
	int i = 1;
	int j = 0;
	int sep_count = sep_len(av);
	int flag = 1;
	if (!sep_count)
		flag = 0;
	while (av[i]) 
	{
        if (av[i][0] != '|' && ft_strlen(av[i]) != 1) 
		{
            if (joined == NULL) 
			{
                joined = ft_strdup(av[i]);
            } 
			else 
			{
                joined = ft_strjoin(joined, " ");
                joined = ft_strjoin(joined, av[i]);
            }
        }
		if (!av[i + 1])
		{
			if (joined)
			{
				bonus_child_fork_1(ac, av, envp, array, command);
				free(joined);
				joined = NULL;
			}
		} 
		else if ((av[i][0] == '|' && ft_strlen(av[i]) == 1)) 
		{
            command = ft_strdup(joined);
            if (joined != NULL) 
			{
                free(joined);
                joined = NULL;
            }
            // execute func
			if (flag == 1)
			{			
				while_loop_fork(arr, av, envp, array, command);
			}
			else
			{
				bonus_child_fork_1(ac, av, envp, array, command);
			}
            free(command);
            command = NULL;
            joined = NULL;
        }
        i++;
    }
	 
}
		

int	main(int ac, char **av, char *envp[])
{
	int		**array;
	pid_t	f1;
	pid_t	f2;
	pid_t	fn;
	int		arr[4];

	//protection(ac);
	arr[0] = ac;
	arr[1] = 0;
	// if (!(ft_strncmp(av[1], "here_doc", ft_strlen("here_doc"))))
	// 	heredoc_(ac, av, envp);
	array = handling_multiple_pipes(av);
	arr[2] = 0;
	while (arr[2] < sep_len(av))
	{
		if (pipe(array[(arr[2])++]) == -1)
			exit(1);
	}
	checking_if_pipe_exists(ac, av,envp, array, arr);
	// f1 = bonus_child_fork_1(ac, av, envp, array);
	 //fn = while_loop_fork(arr, av, envp, array);
	// f2 = bonus_child_fork_2(arr, av, envp, array);
	// closing_pipes(ac, array);
	waitpid(fn, NULL, 0);
	
	
}
