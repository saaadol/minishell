/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:56:50 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 14:35:48 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_listt(t_env *list)
{
	t_env	*tmp;
	t_env	*tmp1;

	if (list)
	{
		tmp = list;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			free(tmp->cmd);
			free(tmp->str);
			free(tmp);
			tmp = tmp1;
		}
	}
}

t_env	*ft_cr_listt(char *cmd, char *str, int i)
{
	t_env	*s;

	s = (t_env *)malloc(sizeof(t_env));
	if (!s)
		return (NULL);
	s->cmd = ft_strdup(cmd);
	if (!str)
		s->str = NULL;
	else
		s->str = ft_strdup(str);
	s->v = i;
	s->next = NULL;
	return (s);
}

void	ft_add_endd(t_env **a, t_env *n)
{
	t_env	*tmp;

	tmp = *a;
	if (*a == NULL)
	{
		*a = n;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = n;
}

t_env	*get_env(char **env, t_env *envs)
{
	t_env	*en;
	char	*str;

	while (*env)
	{
		str = ft_strchr(*env, '=');
		if (str)
		{
			*str = '\0';
			en = ft_cr_listt(*env, str + 1, 0);
			ft_add_endd(&envs, en);
		}
		env++;
	}
	return (envs);
}
