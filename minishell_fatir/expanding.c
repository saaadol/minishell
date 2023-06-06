/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:29:19 by afatir            #+#    #+#             */
/*   Updated: 2023/06/04 12:39:18 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_free_expand(t_var *v)
{
	char	*cmd;

	cmd = ft_strdup(v->c);
	free(v->c);
	free(v);
	return (cmd);
}

char	*expander(char *cmd, t_env **env)
{
	int		i;
	t_var	*v;

	i = 0;
	v = (t_var *)malloc(sizeof(t_var));
	v->c = ft_strdup("");
	v->k = ft_strlen(cmd);
	while (i < v->k)
	{	
		if (cmd[i] && is_sep(cmd[i], 2))
			i = sep_case(cmd, i, v, env);
		else
			i = else_case(cmd, i, v, env);
		i++;
	}
	return (ft_free_expand(v));
}

void	expanding(t_list **arg, t_env **envs)
{
	int		i;
	t_list	*cur;
	char	*p;

	i = 0;
	p = NULL;
	cur = *arg;
	while (cur != NULL)
	{	
		while (cur->str[i])
		{
			if (cur->str[i] == '$')
			{
				p = expander(cur->str, envs);
				free(cur->str);
				cur->str = ft_strdup(p);
				free(p);
				break ;
			}
			i++;
		}
		i = 0;
		cur = cur->next;
	}
}
