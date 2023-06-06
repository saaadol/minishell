/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 08:12:54 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 15:29:13 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expo_exist_norm(char *str, t_env **env, int i)
{
	char	*c;
	t_env	*cur;

	cur = *env;
	if (i == 1)
	{
		if (str)
		{
			c = ft_strdup(cur->str);
			free(cur->str);
			cur->str = dupping(c, ft_strdup(str + 1));
		}
	}
	else if (i == 2)
	{
		free(cur->str);
		cur->str = ft_strdup(str + 1);
	}
}

int	expo_exist(char *arg, int i, t_env **envs)
{
	t_env	*cur;
	char	*str;
	char	*s;

	s = ft_strndup(arg, 0, i);
	cur = *envs;
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->cmd, s))
		{
			str = ft_strchr(arg, '=');
			if (*(str - 1) == '+')
				return (expo_exist_norm(str, &cur, 1), free(s), 1);
			else if (*(str - 1) != '+' && cur->v == 0)
				return (expo_exist_norm(str, &cur, 2), free(s), 1);
			else
			{
				cur->str = ft_strndup(arg, i + 1, ft_strlen(arg));
				cur->v = 0;
				return (free(s), 1);
			}
		}
		cur = cur->next;
	}
	return (free(s), 0);
}

int	export_valid(char *arg, t_env **envs)
{
	t_env	*en;
	char	*str;
	int		i;

	i = 0;
	if (is_valide(arg) == 2)
		return (ft_export(arg, envs));
	if (!is_valide(arg))
		return (0);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		i--;
	if (expo_exist(arg, i, envs))
		return (1);
	str = ft_strchr(arg, '=');
	if (str)
	{
		*str = '\0';
		en = ft_cr_listt(arg, str + 1, 0);
		ft_add_endd(envs, en);
	}
	return (1);
}

int	export(t_list **args, t_env **envs)
{
	t_list	*arg;
	t_env	*env;

	arg = *args;
	env = *envs;
	while (arg != NULL)
	{
		if (arg->next != NULL && !ft_strcmp(arg->str, "export"))
		{
			while (arg->next != NULL)
			{
				if (arg->next && !export_valid(arg->next->str, envs))
					return (0);
				arg = arg->next;
			}
		}
		if (arg->next == NULL && !ft_strcmp(arg->str, "export"))
			print_env_xp(*envs);
		if (arg && !ft_strcmp(arg->str, "env"))
			print_env(*envs);
		arg = arg->next;
	}
	return (1);
}
