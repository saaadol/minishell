/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:34:06 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 15:11:52 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep_valid(char *str, char *next)
{
	int		i;

	i = 0;
	if ((str[i] == '>' || str[i] == '<') && \
		(next[i] == '|' || (next[i] == '>' || next[i] == '<')))
		return (0);
	if (str[i] == '|' && next[i] == '|')
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			if (ft_strlen(str) > 2)
				return (0);
		if (str[i] == '|')
			if (ft_strlen(str) > 1)
				return (0);
		i++;
	}
	return (1);
}

int	check_syntax(t_list **arg)
{
	t_list	*cur;

	if (arg && *arg)
	{
		cur = *arg;
		if (*cur->str == '|')
			return (0);
		while (cur != NULL)
		{
			if (is_sep(*cur->str, 1))
			{
				if (!cur->next || !check_sep_valid(cur->str, cur->next->str))
					return (0);
				cur->type = SEP;
			}
			else
				cur->type = WORD;
			if (!ft_strcmp(cur->str, "&&") || !ft_strcmp(cur->str, "&"))
				return (0);
			cur = cur->next;
		}
	}
	return (1);
}
