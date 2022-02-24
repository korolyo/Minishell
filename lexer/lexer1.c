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

char	*lexer_redir(t_tlist **tokens, char *prompt, int i)
{
	char	*str;
	int 	j;
	t_tlist	*tmp_head;
	int 	type;

	j = i;
	printf("check\n");
	tmp_head = *tokens;
	if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		type = HERE_DOC;
		i++;
	}
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		type = REDIR_APPEND;
		i++;
	}
	else if (prompt[i] == '>')
		type = REDIR;
	else if (prompt[i] == '<')
		type = REDIR_INPUT;
	i++;
	if (prompt[i] == ' ')
		i++;
	while (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i]))
		i++;

	// DIFFERENT FUNCTION:
	while (tmp_head->next)
		tmp_head = tmp_head->next;
	if (type == REDIR)
	{
		str = ft_substr(prompt, j + 1, i - j - 1);
		tmp_head->fdout = open(str, O_WRONLY | O_CREAT | O_TRUNC,
							   0644);
	}
	if (type == REDIR_APPEND)
	{
		str = ft_substr(prompt, j + 2, i - j - 2);
		tmp_head->fdout = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (type == REDIR_INPUT)
	{
		str = ft_substr(prompt, j + 1, i - j - 2);
		tmp_head->fdin = open(str, O_RDONLY, 0644);
		if (tmp_head->fdin == -1)
			printf("%s: No such file or directory", str);
	}
	if (type == HERE_DOC)
	{
		tmp_head->fdin = 0;
		tmp_head->fdout = 1;
	}
	str = str_delete_part(prompt, j, i - 1, DELETE_MID);
	return (str);
}

void	lexer_cmd(t_tlist **tokens, char *prompt)
{
	t_tlist	*tmp;
	char 	*tmp_str;
	int 	j;
	int		count;

	count = -1;
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

char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp)
{
	t_tlist	*tmp_cmds;
	char	*str_before;
	char 	*str_after;

	str_before = ft_substr(tmp, 0, *i);
	lexer_cmd(tokens, str_before);
	tmp_cmds = *tokens;
	tmp_cmds->pipes++;
	printf("check pipes = %d\n", (*tokens)->pipes);
	str_after = ft_substr(tmp, *i + 1, ft_strlen(tmp) - *i);
	*i = -1;
	free(tmp);
	return (str_after);
}
