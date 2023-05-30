/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:57:42 by souledla          #+#    #+#             */
/*   Updated: 2023/05/27 09:58:20 by souledla         ###   ########.fr       */
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