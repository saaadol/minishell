/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:33:51 by afatir            #+#    #+#             */
/*   Updated: 2023/06/04 12:36:17 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_str(char *cmd, t_env **env)
{
	t_env	*cur;
	char	*str;

	cur = *env;
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->cmd, cmd))
		{
			str = ft_strdup(cur->str);
			return (free(cmd), str);
		}
		cur = cur->next;
	}
	return (free(cmd), NULL);
}

int	get_expande(char *cmd, int i, t_env **env, t_var *v)
{
	int		b;

	b = ++i;
	while (cmd[i] && cmd[i] != '$' && !is_sep(cmd[i], 1) && \
		!is_sep(cmd[i], 2) && !is_sep(cmd[i], 3))
		i++;
	v->str = ft_strndup(cmd, b, i--);
	v->str = get_env_str(v->str, env);
	if (v->str)
		v->c = dupping(v->c, v->str);
	return (i);
}

int	sep_case(char *cmd, int i, t_var *v, t_env **env)
{
	v->j = get_index(i, cmd);
	if (cmd[v->j] == '\"')
	{
		v->b = i;
		while (i <= v->j && cmd[i])
		{
			if (cmd[i] == '$')
				i = get_expande(cmd, i, env, v);
			else
			{
				v->c = ft_strjoin_p(v->c, cmd[i]);
				v->b = i;
			}
			i++;
		}
		i--;
	}
	else
	{
		v->f = ft_strndup(cmd, i, v->j + 1);
		v->c = dupping(v->c, v->f);
		i = v->j;
	}
	return (i);
}

int	else_case(char *cmd, int i, t_var *v, t_env **env)
{
	while (cmd[i] && !is_sep(cmd[i], 2))
	{
		v->b = i;
		if (cmd[i] == '$')
		{
			v->f = ft_strndup(cmd, v->b, i);
			v->c = dupping(v->c, v->f);
			i = get_expande(cmd, i, env, v);
		}
		else
			v->c = ft_strjoin_p(v->c, cmd[i]);
		i++;
	}
	i--;
	return (i);
}
