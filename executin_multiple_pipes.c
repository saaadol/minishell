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






pid_t	while_loop_fork(int *arr, char **av, char *envp[], int **array, char *command, int *fd, pid_t *array_of_pids, int *infile , int *outfile)
{
	pid_t	fn;
	int		i;
	static int j  = 0;
	char **splited_command = NULL;
	splited_command = ft_split(command, ' ');
	 //printf("%d", *outfile);
	// exit(1);
	i = 0;

	fn = fork();
	if (fn == 0)
	{
		if (j != 0)
		{
			if (*infile != -99)
				dup2(*infile, 0);
			else
				dup2(array[j - 1][0], 0);
			if (*outfile != -99)
			{
				dup2(*outfile, 1);
				close(*outfile);
				*outfile = -99;
			}
			else
				dup2(array[j][1], 1);
		}
		else
		{
			if (*infile != -99)
				dup2(*infile, 0);
			if (*outfile != -99)
			{
				dup2(*outfile, 1);
				close(*outfile);
			}
			else 
				dup2(array[0][1], 1);
			//  else
			// 	dup2(array[0][0], 0);
		} 	

		while (i < sep_len(av))
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		//execve(checking_path(envp, splited_command[0]), splited_command, envp);
		exec_function(envp, splited_command, splited_command[0]);
		
	}
	array_of_pids[j] = fn;
	*fd = j;
	*outfile = -99;
	*infile = -99;
	//printf("%d", *infile);
	j++;
	i = 0;
	while (splited_command[i])
	{
		free(splited_command[i++]);
	}
	free(splited_command);
	return fn;
	//waitpid(fn, NULL, 0);
	// return (fn);
}

pid_t	bonus_child_fork_1(int ac, char **av, char *envp[], int **array, char *command, int fd_, int infile, int outfile)
{
	pid_t	f1;

	char **splited_command = NULL;
	int		i;
	i = 0 ;
	splited_command = ft_split(command, ' ');
	
	f1 = fork();
	if (f1 == 0)
	{	
		if (infile != -99)
		{
			dup2(infile, 0);
			close(infile);
		}
		else if (fd_  != -1)
		{
			dup2(array[fd_][0], 0);
			
		}
		if (outfile != -99)
		{
			// if (fd_ == -1)
			// {
				dup2(outfile, 1);
				close(outfile);
			// }

		}
		else if (infile == -99 && fd_ == -1)	
		{
			dup2(array[0][0], 0);
		}

		while (i < sep_len(av))
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		exec_function(envp, splited_command, splited_command[0]);
		//execve(checking_path(envp, splited_command[0]), splited_command, envp);
	}

	i = 0;
	while (splited_command[i])
	{
		free(splited_command[i++]);
	}
	free(splited_command);
	                                                                                                                                                                                                                                                                                      
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

pid_t *creating_array_of_fds(char **av)
{
	pid_t *array = malloc(sizeof(pid_t ) * sep_len(av));

	return array;
}


int redirection_in_fork(char **av, char **envp, int index)
{
	int fd;
	fd = open(av[index + 1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror(av[index + 1]);
		exit(1);
	}
	return fd;
}
int append(char **av, char **envp, int index)
{
	int fd;
	fd = open(av[index + 1], O_CREAT | O_APPEND | O_RDWR , 0777);
	if (fd == -1)
	{
		perror(av[index + 1]);
		exit(1);
	}
	return fd;
} 
int redirection_out_fork(char **av, char **envp, int index)
{
	int fd;
	fd = open(av[index + 1], O_CREAT | O_TRUNC | O_RDWR ,  0777);
	if (fd == -1)
	{
		perror(av[index + 1]);
		exit(1);
	}
	return fd;
}
int heredoc_func(int ac, char **av, char *envp[], char *delimiter)
{                      
	int i = 0;
	char *buffer;
	int	pips[2];
	pipe(pips);

	while (1)
	{
		write(1, "heredoc>", 8);
		buffer = get_next_line(0);
		if (ft_strlen(buffer) == ft_strlen(delimiter) && !ft_strncmp(buffer, delimiter, ft_strlen(delimiter)))
		{
			free(buffer);
			break;
		}
		write(pips[1], buffer, ft_strlen(buffer));
		free(buffer);	
	}
	i = 0;
	close(pips[1]);

	//freeying_pips(pips);
	return pips[0];

}
void checking_if_pipe_exists(int ac, char **av, char **envp, int **array, int *arr)
{
	int redirection_in_flag = 0;
	int redirection_out_flag = 0;
	int heredoc_flag = 0;
	int heredoc_output = -99;
	char *command = NULL;
	pid_t *array_of_pids = creating_array_of_fds(av);
	char *joined = NULL;
	int i = 1;
	int j = 0;
	int sep_count = sep_len(av);
	int flag = 1;
	int fd_ = -1;
	int infile = -99;
	int outfile = -99;
	pid_t fd1;
	pid_t fd2;
	if (!sep_count)
		flag = 0;
	while (av[i]) 
	{		
		if (av[i][0] == '<' || av[i][0] == '>')
		{
			if (av[i][0] == '<')
			{
				if (av[i][1] == '<')
				{
					heredoc_flag = 1;
					infile = heredoc_func(ac ,av ,envp, av[i + 1]);
					i++;
				}
				else
				{
					redirection_in_flag = 1;
					infile = redirection_in_fork(av, envp, i);
					i++;
				}
			}
			else
			{
				if (av[i][1] == '>')
				{
					outfile = append(av, envp, i);
					i++;
				}
				else 
				{
					redirection_out_flag = 1;
					outfile = redirection_out_fork(av,envp, i);	
					
					i++;
				}
			}
		}
       	else if (av[i][0] != '|') 
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
				command = ft_strdup(joined);
				fd1 = bonus_child_fork_1(ac, av, envp, array, command, fd_, infile, outfile);
				free(joined);
				free(command);
				command = NULL;
				joined = NULL;
			}
		} 
		else if (av[i][0] == '|') 
		{
			if (joined)
			{
				command = ft_strdup(joined);
				//printf("%s", command);
				
				if (joined != NULL) 
				{
					free(joined);
					joined = NULL;
				}
				fd2 = while_loop_fork(arr, av, envp, array, command, &fd_, array_of_pids, &infile, &outfile);
				free(command);
				command = NULL;
				joined = NULL;
			}
			else
			{
				
				infile = -99;
				outfile = -99;
			}
        }
        i++;
    }
	i = 0;
	while (i < sep_len(av))
	{
		close(array[i][0]);
		close(array[i][1]);
		i++;
	}
	i = 0;

	while (i < sep_len(av))
	{
		waitpid(array_of_pids[i], NULL, 0);
		i++;
	}
	waitpid(fd1, NULL, 0);
	
	free(array_of_pids);
}
		

// int	main(int ac, char **av, char *envp[])
// {
// 	int		**array;
// 	pid_t	f1;
// 	pid_t	f2;
// 	pid_t	fn;
// 	int		arr[4];

// 	//protection(ac);
// 	arr[0] = ac;
// 	arr[1] = 0;
// 	// if (!(ft_strncmp(av[1], "here_doc", ft_strlen("here_doc"))))
// 	// 	heredoc_(ac, av, envp);
// 	array = handling_multiple_pipes(av);
// 	arr[2] = 0;
// 	while (arr[2] < sep_len(av))
// 	{
// 		if (pipe(array[(arr[2])++]) == -1)
// 			exit(1);
// 	}
// 	checking_if_pipe_exists(ac, av,envp, array, arr);
	
// 	// f1 = bonus_child_fork_1(ac, av, envp, array);
// 	 //fn = while_loop_fork(arr, av, envp, array);
// 	// f2 = bonus_child_fork_2(arr, av, envp, array);
// 	// closing_pipes(ac, array);
// 	//waitpid(fn, NULL, 0);
	
	
// }
