/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// DO THE LOGIC
char	*lexer_quotes(char *prompt, int *i, t_list **var_list)
{
	char	*tmp;
	int 	j;

	j = *i;
	tmp = ft_strdup(prompt);
	if (tmp[*i] == '\'')
		preparse_quotes(tmp, i);
	if (tmp[*i] == '\"')
	{
		(*i)++;
		while (tmp[*i] != '\"')
		{
			if (tmp[(*i)] == '$')
			{
				tmp = lexer_dollar(tmp, i, var_list);
				(*i)--;
			}
//			printf("tmp_quotes[%d] = %c\n", *i, tmp[*i]);
//			sleep(1);
			(*i)++;
		}
//		printf("check quotes\n");
	}
	free(prompt);
	return (tmp);
}
//TO DO: var that contain error value
char	*lexer_dollar(char *prompt, int *i, t_list **var_list)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_list	*tmp4;
	t_var	*tmp5;
	int		j;

	tmp = ft_substr(prompt, 0, (*i));
	(*i)++;
	if (is_key(prompt[*i]) || prompt[*i] == '?')
	{
		j = *i;
		if (prompt[*i] == '?')

		while (is_key(prompt[*i]))
			(*i)++;
		tmp2 = ft_substr(prompt, j, (*i) - j);
		tmp3 = ft_substr(prompt, (*i), ft_strlen(prompt) - (*i));
		tmp4 = ft_find_var(var_list, tmp2);
		free(tmp2);
		tmp5 = (t_var *)tmp4->content;
		tmp2 = ft_strdup(tmp5->value);
		*i = j + ft_strlen(tmp2) - 2;
//		printf("*i in dollar = %d\n", *i);
		tmp = ft_strjoin(tmp, tmp2);
		if (tmp2)
			free(tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		if (tmp3)
			free(tmp3);
	}
	if (ft_isdigit(prompt[*i]))
		(*i)++;
	return (tmp);
}

char	*lexer_redir(t_tlist **tokens, char *prompt, int i)
{
	t_tlist	*tmp;
	char	*str;
	char 	*tmp_str;
	int 	j;

	j = i;
	tmp_str = NULL;
	if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		tmp = tlistnew(HERE_DOC);
		i++;
	}
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		tmp = tlistnew(REDIR_APPEND);
		i++;
	}
	else if (prompt[i] == '>')
		tmp = tlistnew(REDIR);
	else if (prompt[i] == '<')
		tmp = tlistnew(REDIR_INPUT);
	i++;
	if (prompt[i] == ' ')
		i++;
	while (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i]))
		i++;
	if (tmp->type == REDIR || tmp->type == REDIR_APPEND ||
		tmp->type == REDIR_INPUT)
		tmp_str = ft_substr(prompt, j, i - j);
//	printf("tmp-str in redir = |%s|\n", tmp_str);
	tmp->cmd = ft_quotes_split(tmp_str, ' ');
//	printf("check redir\n");
	str = str_delete_part(prompt, j, i - 1, DELETE_MID);
	tlistadd_back(tokens, tmp);
	return (str);
}

void	lexer_cmd(t_tlist **tokens, char *prompt)
{
	t_tlist	*tmp;
	char 	*tmp_str;
//	char 	*tmp_str1;
	int 	j;
	int		count;

	count = -1;
	j = -1;
//	printf("check cmd\n");
	tmp = tlistnew(CMD);
	tlistadd_back(tokens, tmp);
	tmp_str = prompt;
	while (tmp_str[++j])
	{
//		printf("check\n");
//		printf("tmp-str in cmd = |%s|\n", tmp_str);
//		printf("tmp-str in cmd = |%c|\n", tmp_str[j]);
		if (tmp_str[j] == '\'' || tmp_str[j] == '\"')
		{
			preparse_quotes(tmp_str, &j);
			j--;
		}
		if (ft_strchr("><", tmp_str[j]))
		{
			tmp_str = lexer_redir(tokens, tmp_str, j);
			j = 0;
		}
//		printf("tmp-str in cmd while = |%s|\n", tmp_str);
	}
//	printf("tmp-str in cmd = |%s|\n", tmp_str);
//	printf("prompt = %s\n", prompt);
//	printf("i = %d j = %d\n", *i, j);
//	tmp_str = ft_substr(prompt, j, *i - j);
//	printf("tmp_str = %s\n", tmp_str);
//	printf("check cmd\n");
	tmp->cmd = ft_quotes_split(tmp_str, ' ');
//	while (tmp->cmd[++count])
//		printf("count = %d tlist->cmd = |%s|\n", count, tmp->cmd[count]);
//	printf("cmd check\n");
}

char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp)
{
	t_tlist	*tmp_node;
	char	*str;

	(*i)++;
	str = NULL;
	tmp_node = tlistnew(PIPE);
	tlistadd_back(tokens, tmp_node);
	str = ft_substr(tmp, *i + 1, ft_strlen(tmp) - *i);
	free(tmp);
	*i = -1;
	return (str);
}
