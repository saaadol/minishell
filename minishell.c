/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:27:48 by souledla          #+#    #+#             */
/*   Updated: 2023/05/28 18:07:02 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_fatir/minishell.h"



// void handle_space(t_list **arg, char *str, int i)
// {	
// 	if (is_white_space(str[i + 1]) == 0)
// 	{
// 		char *str1 = malloc(sizeof(char) * i  + 1);
// 		int j = 0;
// 		while(j <= i)
// 		{
// 			str1[j] = str[j];	
// 			j++;
// 		}
// 		str1[j] = '\0';
// 		adding_node(arg); 
		
// 	}		
// 	if (is_alpha_numeric(str[i]) == 1)
// 		return;
// }
// void handle_char(t_list **arg, char *str, int *i, int flag)
// {
// 	int string_begin = *i;
// 	while (str[*i] && (is_alpha_numeric(str[*i]) == 1 ||  is_special_char(str[*i]) == 1)) 
// 		(*i)++;
// 	int string_end = *i -1;
// 	if (flag == 1)
// 		return;
// 	adding_node(arg);
// 	t_list *head = *arg;
// 	while(head && head->next)
// 		head = head->next;
// 	head->string = ft_strndup(str, string_begin, string_end);
// 	return;
// }
// void handle_separator(t_list **arg, char *str, int *i)
// {
// 	int string_begin = *i;
// 	while(str[*i] && is_separator(str[*i]))
// 		(*i)++;	
// 	int string_end = *i - 1;
// 	adding_node(arg);
// 	t_list *head = *arg;
// 	while (head && head->next)
// 		head = head->next;
// 	head->string = ft_strndup(str, string_begin, string_end);
// 	return;
	
// }
// void handle_quote(t_list **arg, char *str, int *i)
// {
// 	char *result = malloc(sizeof(char) * 1);
// 	char *s1 = str + *i;
// 	s1 = ft_strtrim(s1, "\"\'");
// 	result = ft_strjoin(result, s1);
// 	printf("%s", result);
// 	exit(1);
// 	int j = 0;
// 	while (s1[j] && is_quote(s1[j]) != 1)
// 	{
// 		j++;
// 	}
// 	if (s1[j] && is_quote(s1[j]) == 1)
// 	{
// 		s1 = s1 +j;
// 		s1 = ft_strtrim(s1, "\"\'");
// 		result = ft_strjoin(result, s1);
// 		printf("%s", result);
// 		exit(1);
		
// 	}
	


	
//     // int string_begin = *i;
//     // while (str[*i] && is_quote(str[*i]) == 1)
//     // {
//     //     (*i)++;
//     // }
//     // string_begin = *i;
//     // if (is_white_space(str[*i]) == 1 || is_alpha_numeric(str[*i]) == 1)
//     // {
//     //     while (str[*i] && (is_white_space(str[*i]) == 1 || is_alpha_numeric(str[*i]) == 1 || is_special_char(str[*i]) == 1))
//     //     {
//     //         (*i)++;
//     //     }
//     //     int string_end = *i - 1;

//     //     while (str[*i] && is_quote(str[*i]) == 1)
//     //     {
//     //         (*i)++;
//     //     }
//     //     if (str[*i] && (is_white_space(str[*i]) == 1 || is_alpha_numeric(str[*i]) == 1))
//     //     {
//     //         int next_string_begin = *i;
//     //         while (str[*i] && (is_white_space(str[*i]) == 1 || is_alpha_numeric(str[*i]) == 1 || is_special_char(str[*i]) == 1))
//     //         {
//     //             (*i)++;
//     //         }
//     //         int next_string_end = *i - 1;
//     //         string_end = next_string_end;

            
//     //         *i = next_string_end + 1;
//     //     }

//     //     adding_node(arg);
//     //     t_list *head = *arg;
//     //     while (head && head->next)
//     //         head = head->next;
//     //     head->string = ft_strndup(str, string_begin, string_end);
//     // }

//     // return;
// }

// void handle_special_char(t_list **arg, char *str, int *i)
// {
// 	int string_begin = *i;
// 	while(str[*i] && is_special_char(str[*i]) == 1)
// 	{
// 		(*i)++;	
// 	}
// 	if (str[*i] && is_alpha_numeric(str[*i]))
// 	{
// 		handle_char(arg, str, i, 1);
// 	}
// 	int string_end = *i - 1;
// 	adding_node(arg);
// 	t_list *head = *arg;
// 	while (head && head->next)
// 		head = head->next;
// 	head->string = ft_strndup(str, string_begin, string_end);
// 	return;
// }
// void quote_counter(char *str)
// {
// 	int i = 0;
// 	int counter1 = 0;
// 	int counter2 = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 			counter1++;
// 		else if(str[i] == '\'')
// 			counter2++;
// 		i++;
// 	}
// 	if (counter1 % 2 != 0 || counter2 % 2 != 0)
// 	{
// 		printf("syntax error");
// 		exit(1);
// 	}		
// 	return ;	
	
// }
// void tokenizer(t_list **arg, char *argument)
// {
// 	int i = 0;	
//     char *word = ft_strtrim(argument, " ");
// 	quote_counter(word);
// 	while (i < ft_strlen(word))
// 	{
// 		if (is_alpha_numeric(word[i]) == 1)
// 			handle_char(arg, word,  &i, 0);
// 		else if (is_white_space(word[i]) == 1)
// 			i++;
// 		else if (is_separator(word[i]) == 1)
// 		{
// 			handle_separator(arg, word, &i);
// 		}
// 		else if (is_quote(word[i]) == 1)
// 		{
// 			handle_quote(arg, word, &i);
// 		}
// 		else
// 		{
// 			handle_special_char(arg, word, &i);
// 		}
// 	}
// }

// char  *if_double_quote(t_list **arg, char *str)
// {
// 	int flag;
// 	if (ft_strchr(str, '\"'))
// 	{
// 		str = ft_strchr(str, '\"');
// 		if (str[ft_strlen(str)] != '\"')
// 		{
// 			printf("%s\n", str);
// 			exit(1);
// 		}
// 	}
// 	else if (ft_strchr(str, '\''))
// 		str = ft_strchr(str, '\'');
// 	return str;
// }
// char *ft_strndup(char *str, int start, int end)
// {
// 	char *s1 = malloc(sizeof(char) * (end -start + 2));
// 	int j = 0;
// 	int len = end -start;
// 	while(j <= len)
// 	{
// 		s1[j] = str[start];
// 		start++;
// 		j++;
// 	}
// 	s1[j] = '\0';
// 	return s1;
// }
// void adding_node(t_list **arg)
// {
//     t_list *new_node = malloc(sizeof(t_list));
//     new_node->next = NULL;

//     if (*arg == NULL)
// 	{
//         *arg = new_node;
// 	}
//     else
//     {
//         t_list *temp = *arg;
//         while (temp && temp->next != NULL)
//         {
//             temp = temp->next;
//         }
// 		//printf("-%s-\n", temp->string);
//         temp->next = new_node;
//     }
// }

// void  displaying_prompt(t_list *arg)
// { 
// 	int i = 0;
// 	char *argument;
// 	while (1)
// 	{
// 		t_list *arg = NULL;
// 		argument = readline("\033[1;31m>\033[0m ");
// 		if (!ft_strncmp(argument, "exit", ft_strlen("exit")))
// 			break;
// 		tokenizer(&arg, argument);
// 		add_history(argument);
// 		print_nodes(arg);
// 	}
// 	clear_history();
// }



// int main(int ac, char **av, char *env[])
// {
// 	t_list *arg = NULL;
// 	displaying_prompt(arg);
// }


