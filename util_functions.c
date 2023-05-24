/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:13:29 by souledla          #+#    #+#             */
/*   Updated: 2023/05/23 18:25:20 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd()
{
	char buffer[1024];
	if (getcwd(buffer, 1024) == NULL)
		printf("error");
	printf("%s\n", buffer);
}
static int
	string(char character, char  *word)
{
	size_t	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == character)
			return (1);
		i++;
	}
	return (0);
}
int is_alpha_numeric(char x)
{
	if (x >= '0' && x <= '9' || x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z')
		return 1;
	return 0;
}
int is_white_space(char x)
{
	if (x >= 9 && x <= 13 || x == 32)
		return 1;
	return 0;
}
int is_quote(char x)
{
	if (x == '\'' || x == '\"')
		return 1;
	return 0;
}
int is_separator(char x)
{
	if (x == '|' || x == '>' || x == '<')
		return 1;
	return 0;
}
char
	*ft_strtrim(char  *word, char  *delimiter)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (word[start] && string(word[start], delimiter))
		start++;
	end = ft_strlen(word);
	while (end > start && string(word[end - 1], delimiter))
		end--;
	str = (char*)malloc(sizeof(*word) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = word[start++];
	str[i] = 0;
	return (str);
}
char    *ft_strcpy(char *s1, char *s2)
  {
      int i;
 
      i = 0;
      while (s2[i])
      {
          s1[i] = s2[i]; 
          i++;
      }
      s1[i] = s2[i];  
      return (s1);
  }
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*x1;
	unsigned char	*x2;
	size_t			i;

	x1 = (unsigned char *) s1;
	x2 = (unsigned char *) s2;
	i = 0;
	while (i < n && (x1[i] || x2[i]))
	{
		if (x1[i] != x2[i])
			return (x1[i] - x2[i]);
		i++;
	}
	return (0);
}
int is_special_char(char x)
{
	if (!is_alpha_numeric(x) && !is_white_space(x) && !is_separator(x) && !is_quote(x))
		return 1;
	return 0;
}

void print_nodes(t_list *arg)
{
    t_list *current = arg;
    while (current != NULL)
    {
        printf("%s\n", current->string);
        current = current->next;
    }
}
