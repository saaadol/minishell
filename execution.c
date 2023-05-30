/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:58:45 by souledla          #+#    #+#             */
/*   Updated: 2023/05/27 14:45:58 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*located_path_return(char *envp[])
{
	int		i;
	char	*p;
	char	*located_path;

	p = "PATH=";
	i = 0;
	while (envp[i])
	{
		if (ft_newstrchr(envp[i], p))
			located_path = ft_newstrchr(envp[i], p);
		i++;
	}
	if (!located_path)
		exit(1);
	return (located_path);
}
char	*ft_newstrchr(char *s, char *target)
{
	int	i;
	int	len;
	int	j;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!s)
		exit(1);
	while (s[i])
	{
		if (s[i] == target[j])
			j++;
		else if (target[j] == '\0')
			return (s + i);
		i++;
	}
	return (NULL);
}
char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	return (s1 = NULL, p);
}
char	*checking_path(char *envp[], char *comm)
{
	int		i;
	char	*located_path;
	char	**str;

	located_path = located_path_return(envp);
	str = ft_split(located_path, ':');
	i = 0;
	if (ft_newstrchr(comm, "./") || ft_newstrchr(comm, "/"))
		return (comm);
	while (str[i])
	{
		str[i] = ft_join(str[i], ft_join("/", comm));
		if (access(str[i], F_OK) == 0)
			return (str[i]);
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}


void	while_pipe(int **pips)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pipe(pips[i++]) == -1)
			exit(1);
	}
}

void exec_command(char *envp[], char **command, char *x, int ac, char **av)
{
	int fd;
	fd = open(command[0], O_RDONLY, 0777);
	
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
		if (execve(checking_path(envp, command[0]),command,envp) == -1)
		{
			close(fd);
			perror(x);
			exit(1);
		}
	}
}
pid_t child_fork_heredoc_1(int ac, char **av, char *envp[], int **pips) {
    pid_t pid;
    char **command;
    pid = fork();
    if (pid == 0) {
        command = ft_split(av[3], ' ');
		 
        {
            dup2(pips[0][0], 0);
            dup2(pips[1][1], 1);
            int i = 0;
            while (i < 2) {
                close(pips[i][0]);
                close(pips[i][1]);
                i++;
            }
            exec_command(envp, command, av[3], ac, av);
        }
    }
    return pid;
}

pid_t child_fork_heredoc_2(int ac, char **av, char *envp[], int **pips) {
    pid_t pid;
    int fd;
    char **command;
    pid = fork();
    if (pid == 0) {
        fd = open(av[5], O_CREAT | O_TRUNC | O_WRONLY, 0777);
        command = ft_split(av[4], ' ');
        dup2(fd, 1);
        close(fd);
        dup2(pips[1][0], 0);
        int i = 0;
        while (i < 2) {
            close(pips[i][0]);
            close(pips[i][1]);
            i++;
        }
        exec_command(envp, command, av[4], ac, av);
    }
    return pid;
}

void freeying_pips(int **pips)
{
	int  i = 0;
	while (i < 2)
	{
		free(pips[i]);
		i++;
	}
	free(pips);
}
void	executing_func(int ac,char **av, char *envp[], int **pips)
{
	pid_t	pid;
	pid_t	pid2;
	int		i;

	pid = child_fork_heredoc_1(ac, av, envp, pips);
	pid2 = child_fork_heredoc_2(ac, av, envp, pips);
	i = 0;
	while (i < 2)
	{
		close(pips[i][0]);
		close(pips[i][1]);
		i++;
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
void heredoc_(int ac, char **av, char *envp[])
{
	int **pips;                        
	int i = 0;
	char *buffer;
	pips = malloc(sizeof(int *) * 2);
	while (i < 2)
		pips[i++] = malloc(sizeof(int) * 2);
	while_pipe(pips);
	while (1)
	{
		write(1, "heredoc>", 8);
		buffer = readline(0);
		if (!ft_strncmp(buffer, av[2], ft_strlen(av[1])))
		{
			free(buffer);
			break;
		}
		write(pips[0][1], buffer, ft_strlen(buffer));
		free(buffer);
	
	}
	i = 0;
	executing_func(ac, av, envp, pips);	
	freeying_pips(pips);
}
// int main(int ac, char **av, char *envp[])
// {
// 	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
// 		heredoc_(ac, av, envp);
// }


