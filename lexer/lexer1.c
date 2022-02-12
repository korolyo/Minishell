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
//	tmp = prompt;
	if (prompt[*i] == '\'')
	{
		(*i)++;
		while (prompt[(*i)] != '\'')
			(*i)++;
		tmp = str_delete_part(prompt, j, *i, MID);
	}
	if (prompt[*i] == '\"')
	{
		(*i)++;
		while (prompt[*i] != '\"' && prompt[*i] != '$')
		{
			printf("prompt[i] = %c\n", prompt[*i]);
			(*i)++;
			sleep(1);
		}
		printf("check quotes\n");
		if (prompt[(*i)] == '$')
			tmp = lexer_dollar(prompt, i, var_list);
	}
	free(prompt);
	return (tmp);
}
//TO DO: global var(?) that contain error value
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
		while (is_key(prompt[*i]))
			(*i)++;
		tmp2 = ft_substr(prompt, j, (*i) - j);
		tmp3 = ft_substr(prompt, (*i), ft_strlen(prompt) - (*i));
		tmp4 = ft_find_var(var_list, tmp2);
		free(tmp2);
		tmp5 = (t_var *)tmp4->content;
		tmp2 = ft_strdup(tmp5->value);
		*i = j + ft_strlen(tmp2) - 1;
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
	int 	j;

	j = i;
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
	while (prompt[i] == ' ' || ft_isalpha(prompt[i])
		|| ft_isdigit(prompt[i]))
		i++;
	if (tmp->type == REDIR || tmp->type == REDIR_APPEND ||
		tmp->type == REDIR_INPUT)
		tmp->cmd[1] = ft_substr(prompt, j + 1, i - j);
	str = str_delete_part(prompt, j, i, DELETE_MID);
	tlistadd_back(tokens, tmp);
	return (str);
}

void	lexer_cmd(t_tlist **tokens, char *prompt, int *i, t_list **var_list)
{
	t_tlist	*tmp;
	char 	*tmp_str;
	char 	*tmp_str1;
	int 	j;
	int		count;

	count = -1;
	j = -1;
	tmp = tlistnew(CMD);
	while (!ft_strchr("<>|", prompt[(*i)]))
		(*i)++;
	while (tmp_str[++j])
	{
		if (ft_strchr(DELIM, tmp_str[j]))
			i++;
		if (tmp_str[j] == '\'' || tmp_str[j] == '\"')
			tmp_str1 = lexer_quotes(tmp_str, &j, var_list);
		if (ft_strchr("><", tmp[j]))
			tmp_str1 = lexer_redir(tokens, tmp, j);
		if (tmp_str[j] == '$')
			tmp_str1 = lexer_dollar(tmp_str, &j, var_list);
	}
//	printf("prompt = %s\n", prompt);
//	printf("i = %d j = %d\n", *i, j);
//	tmp_str = ft_substr(prompt, j, *i - j);
//	printf("tmp_str = %s\n", tmp_str);
	tmp->cmd = ft_quotes_split(prompt, ' ');
	while (tmp->cmd[++count])
		printf("count = %d tlist->cmd = |%s|\n", count, tmp->cmd[count]);
//	printf("cmd check\n");
	tlistadd_back(tokens, tmp);

}

char	*lexer_pipe(t_tlist **tokens, int *i)
{
	t_tlist	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	tmp = tlistnew(PIPE);
	tlistadd_back(tokens, tmp);
	return (str);
}
