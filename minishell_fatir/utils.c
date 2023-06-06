/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:34:10 by afatir            #+#    #+#             */
/*   Updated: 2023/06/05 13:11:01 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(t_list *arg)
{
	t_list	*current;

	current = arg;
	while (current != NULL)
	{
		printf("[%s][%d]\n", current->str, current->type);
		current = current->next;
	}
	printf("%d\n", ft_strlen_stack(&arg));
}

int	not_sep(char c)
{
	if (!is_sep(c, 1) && !is_sep(c, 2) && !is_sep(c, 3))
		return (1);
	return (0);
}

int	is_sep(char c, int x)
{
	if (x == 1)
	{
		if (c == '|' || c == '>' || c == '<')
			return (1);
		return (0);
	}
	else if (x == 2)
	{
		if (c == '\'' || c == '\"')
			return (1);
		return (0);
	}
	else if (x == 3)
	{
		if (c == 32 || c == 9)
			return (1);
		return (0);
	}
	return (0);
}

char	*dupping(char *str, char *p)
{
	int		i;
	int		j;
	int		k;
	char	*c;

	j = 0;
	k = 0;
	i = ft_strlen(str);
	c = malloc(sizeof(char) * (ft_strlen(p) + i + 1));
	if (!c)
		return (NULL);
	while (j < i)
	{
		c[j] = str[j];
		j++;
	}
	i = ft_strlen(p);
	while (k < i)
	{	
		c[j++] = p[k++];
	}
	c[j] = '\0';
	return (free(p), free(str), c);
}
