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

char	*lexer_dollar(char *prompt, int *i, t_list **var_list)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	tmp = ft_substr(prompt, 0, (*i));
	(*i)++;
	j = 0;
	if (prompt[*i] == ' ' || prompt[*i] == '\0')
		tmp2 = ft_strdup("$");
	if (ft_isdigit(prompt[*i]))
		(*i)++;
	else if (is_key(prompt[*i]) || prompt[*i] == '?')
	{
		j = *i;
		while (is_key(prompt[*i]) || prompt[*i] == '?')
			(*i)++;
		tmp2 = ft_substr(prompt, j, (*i) - j);
	}
	tmp3 = ft_substr(prompt, (*i), ft_strlen(prompt) - (*i));
	tmp2 = find_value(var_list, tmp2);
	*i = j + ft_strlen(tmp2) - 3;
	free(prompt);
	tmp = join_dollar(tmp, tmp2, tmp3);
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

void	open_file(char *name, int type, t_tlist **tmp_head)
{
	if (type == REDIR)
		(*tmp_head)->fdout = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == REDIR_APPEND)
		(*tmp_head)->fdout = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == REDIR_INPUT)
		(*tmp_head)->fdin = open(name, O_RDONLY, 0644);
	if (type == HERE_DOC)
		(*tmp_head)->stop_word = ft_strdup(name);
	if (name)
		free(name);
}

char	*lexer_redir(t_tlist **tokens, char *prompt, int i)
{
	int		j;
	t_tlist	*tmp_head;
	int		type;
	int		k;
	char	*name;

	j = i;
	name = NULL;
	tmp_head = *tokens;
	type = find_type(prompt, j, &i);
	k = i;
	while (ft_isalpha(prompt[i]) || ft_isdigit(prompt[i]))
		i++;
	while (tmp_head->next)
		tmp_head = tmp_head->next;
	if (type == REDIR)
		name = ft_substr(prompt, k, i - j - 1);
	else if (type == REDIR_INPUT || type == REDIR_APPEND || type == HERE_DOC)
		name = ft_substr(prompt, k, i - j - 2);
	open_file(name, type, &tmp_head);
	return (str_delete_part(prompt, j, i - 1, DELETE_MID));
}

void	lexer_cmd(t_tlist **tokens, char *cmd)
{
	t_tlist	*tmp_list;
	char	*tmp_cmd;
	int		j;

	j = -1;
	tmp_list = tlistnew(CMD);
	tlistadd_back(tokens, tmp_list);
	tmp_cmd = cmd;
	while (tmp_cmd[++j])
	{
		if (tmp_cmd[j] == '\'' || tmp_cmd[j] == '\"')
		{
			preparse_quotes(tmp_cmd, &j);
			j--;
		}
		if (ft_strchr("><", tmp_cmd[j]))
		{
			tmp_cmd = lexer_redir(tokens, tmp_cmd, j);
			j = -1;
		}
	}
	tmp_list->cmd = ft_quotes_split(tmp_cmd, ' ');
	if (tmp_cmd)
		free(tmp_cmd);
}
