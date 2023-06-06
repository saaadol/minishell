/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:12:32 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 15:29:29 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *arg)
{
	t_env	*current;

	current = arg;
	while (current != NULL)
	{	
		if (!current->v)
			printf("%s=%s\n", current->cmd, current->str);
		current = current->next;
	}
}

void	print_env_xp(t_env *arg)
{
	t_env	*current;

	current = arg;
	while (current != NULL)
	{
		if (!current->v)
			printf("declare -x %s=\"%s\"\n", current->cmd, current->str);
		else
			printf("declare -x %s\n", current->cmd);
		current = current->next;
	}
}

int	is_valide(char *arg)
{
	int		i;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && (arg[i + 1] != '='))
			return (0);
		if (!ft_isalnum(arg[i]) && arg[i] != '_' \
			&& arg[i] != '\\' && arg[i] != '+')
			return (0);
		i++;
	}
	if (arg[i] == '\0')
		return (2);
	return (1);
}

int	ft_export(char *arg, t_env **envs)
{
	t_env	*en;
	t_env	*cur;

	cur = *envs;
	while (cur)
	{
		if (!ft_strcmp(cur->cmd, arg))
			return (1);
		cur = cur->next;
	}
	en = ft_cr_listt(arg, NULL, 1);
	ft_add_endd(envs, en);
	return (1);
}
