/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:24:51 by afatir            #+#    #+#             */
/*   Updated: 2023/06/01 17:27:06 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, int start, int end)
{
	char	*s1;
	int		i;
	int		len;

	i = 0;
	if (!str)
		str = ft_strdup("");
	len = end - start;
	s1 = ft_calloc(sizeof(char), (len + 1));
	while (len--)
		s1[i++] = str[start++];
	return (s1);
}

int	get_index(int i, char *cmd)
{
	if (cmd[i] && cmd[i] == '\"')
	{
		i++;
		while (cmd[i] && cmd[i] != '\"')
			i++;
	}
	if (cmd[i] && cmd[i] == '\'')
	{
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
	}
	return (i);
}

int	handle_quote(t_list **arg, char *cmd, int i)
{
	int		j;
	t_list	*nl;

	nl = NULL;
	j = i;
	while (cmd[i])
	{
		if (is_sep(cmd[i], 2))
			i = get_index(i, cmd);
		if (is_sep(cmd[i], 1) || is_sep(cmd[i], 3))
			break ;
		i++;
	}
	nl = ft_cr_list(ft_strndup(cmd, j, i));
	ft_add_end(arg, nl);
	return (i);
}

int	handle_sep(t_list **arg, char *cmd, int i)
{
	int		j;
	t_list	*nl;

	nl = NULL;
	j = i;
	while (cmd[i] && is_sep(cmd[i], 1))
		i++;
	nl = ft_cr_list(ft_strndup(cmd, j, i));
	ft_add_end(arg, nl);
	return (i);
}

int	is_char(t_list **arg, char *cmd, int i)
{
	int		j;
	t_list	*nl;

	nl = NULL;
	j = i;
	while (cmd[i] && !is_sep(cmd[i], 1))
	{
		if (is_sep(cmd[i], 3))
			break ;
		if (is_sep(cmd[i], 2))
		{
			while (cmd[i] && !is_sep(cmd[i], 1))
			{
				if (is_sep(cmd[i], 2))
					i = get_index(i, cmd);
				if (is_sep(cmd[i + 1], 3))
					break ;
				i++;
			}
		}
		i++;
	}
	nl = ft_cr_list(ft_strndup(cmd, j, i));
	ft_add_end(arg, nl);
	return (i);
}
