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

char	*lexer_quotes(char *prompt, int *i, t_list **var_list)
{
	char	*tmp;

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
			(*i)++;
		}
	}
	free(prompt);
	return (tmp);
}

//TODO: var that contain error value
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
	j = 0;
	tmp2 = NULL;
	if (prompt[*i] == ' ' || prompt[*i] == '\0')
		tmp2 = ft_strdup("$");
	if (ft_isdigit(prompt[*i]))
		(*i)++;
	else if (is_key(prompt[*i]) || prompt[*i] == '?')
	{
		j = *i;
		if (prompt[*i] == '?')
			tmp = ft_strdup("HZ");
		else
		{
			while (is_key(prompt[*i]))
				(*i)++;
			tmp2 = ft_substr(prompt, j, (*i) - j);
		}
	}
	tmp3 = ft_substr(prompt, (*i), ft_strlen(prompt) - (*i));
	if (tmp2)
	{
		tmp4 = ft_find_var(var_list, tmp2);
		if (!tmp4 && tmp2[0] != '$')
			tmp2 = NULL;
		else if (tmp4)
		{
			tmp5 = (t_var *) tmp4->content;
			tmp2 = ft_strdup(tmp5->value);
		}
	}
	*i = j + ft_strlen(tmp2) - 2;
	tmp = ft_strjoin(tmp, tmp2);
	if (tmp2)
		free(tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	if (tmp3)
		free(tmp3);
	return (tmp);
}

int	find_type(char *prompt, int j, int *i)
{
	int	type;

	type = 0;
	if (prompt[j] == '<' && prompt[j + 1] == '<')
		type = HERE_DOC;
	else if (prompt[j] == '>' && prompt[j + 1] == '>')
		type = REDIR_APPEND;
	else if (prompt[j] == '>')
		type = REDIR;
	else if (prompt[j] == '<')
		type = REDIR_INPUT;
	while (prompt[*i] == ' ' || prompt[*i] == '>' || prompt[*i] == '<')
		(*i)++;
	return (type);
}

char	*lexer_redir(t_tlist **tokens, char *prompt, int i)
{
	char	*str;
	int		j;
	t_tlist	*tmp_head;
	int		type;
	int		k;

	j = i;
	tmp_head = *tokens;
	type = find_type(prompt, j, &i);
	k = i;
	while (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i]))
		i++;
	while (tmp_head->next)
		tmp_head = tmp_head->next;
	if (type == REDIR)
	{
		str = ft_substr(prompt, k, i - j - 1);
		tmp_head->fdout = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (type == REDIR_APPEND)
	{
		str = ft_substr(prompt, k, i - j - 2);
		tmp_head->fdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (type == REDIR_INPUT)
	{
		str = ft_substr(prompt, k, i - j - 2);
		tmp_head->fdin = open(str, O_RDONLY, 0644);
	}
	if (type == HERE_DOC)
		tmp_head->stop_word = ft_substr(prompt, k, i - j - 2);
	str = str_delete_part(prompt, j, i - 1, DELETE_MID);
	return (str);
}

void	lexer_cmd(t_tlist **tokens, char *prompt)
{
	t_tlist	*tmp;
	char	*tmp_str;
	int		j;

	j = -1;
	tmp = tlistnew(CMD);
	tlistadd_back(tokens, tmp);
	tmp_str = prompt;
	while (tmp_str[++j])
	{
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
	}
	tmp->cmd = ft_quotes_split(tmp_str, ' ');
}
