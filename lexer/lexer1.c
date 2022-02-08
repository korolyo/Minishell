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

//void	lexer_backslash(t_tlist **tokens, char *prompt, int *i)
//{
//	t_tlist	*tmp;
//
//	tmp = tlistnew("\\", BACKSLASH, &prompt[*i]);
//	tlistadd_back(tokens, tmp);
//}
//
//void	lexer_semicolon(t_tlist **tokens)
//{
//	t_tlist	*tmp;
//
//	tmp = tlistnew(";", SEMICOLON, NULL);
//	tlistadd_back(tokens, tmp);
//}

// DO THE LOGIC
void	lexer_quotes(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	int 	j;

	j = *i;
	if (prompt[*i] == '\'')
	{
		while (prompt[(*i)] != '\'')
			i++;
		tmp = tlistnew("\'", QUOTES, NULL);
	}
	if (prompt[*i] == '\"')
	{
		while (prompt[(*i)] != '\"')
			i++;
		tmp = tlistnew("\"", QUOTES, NULL);
	}
	tlistadd_back(tokens, tmp);
}

void	lexer_redir(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	int 	j;

	j = *i + 1;
	if (prompt[*i] == '<' && prompt[(*i) + 1] == '<')
	{
		tmp = tlistnew("<<", HERE_DOC, NULL);
		(*i)++;
	}
	else if (prompt[*i] == '>' && prompt[(*i) + 1] == '>')
	{
		tmp = tlistnew(">>", REDIR_APPEND, NULL);
		(*i)++;
	}
	else if (prompt[*i] == '>')
		tmp = tlistnew(">", REDIR, NULL);
	else if (prompt[*i] == '<')
		tmp = tlistnew("<", REDIR_INPUT, NULL);
	while (prompt[*i] == ' ' || ft_isalpha(prompt[*i])
		|| ft_isdigit(prompt[*i]))
		i++;
	if (tmp->type == REDIR || tmp->type == REDIR_APPEND ||
		tmp->type == REDIR_INPUT)
		tmp->args = ft_substr(prompt, j, *i - j);
	tlistadd_back(tokens, tmp);
}

void	lexer_cmd(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	int 	j;

	j = *i;
	while (!ft_strchr(" \t$<>|;", prompt[(*i)]))
		(*i)++;
	tmp = tlistnew(NULL, CMD, NULL);
	tmp->cmd = ft_substr(prompt, j, *i - j);
	printf("tlist->cmd = |%s|\n", tmp->cmd);
	if (prompt[*i] == '-')
	{
		j = *i;
		(*i)++;
		while (ft_isalpha(prompt[*i]))
			(*i)++;
		tmp->args = ft_substr(prompt, j, *i - j);
	}
	tlistadd_back(tokens, tmp);
}

void	lexer_env(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist *tmp;
	int j;

	(*i)++;
	j = *i;
	tmp = tlistnew("$", ENV, NULL);
	if (!(ft_isalpha(prompt[*i])) || prompt[*i] != '?')
		tmp->args = NULL;
	else if (prompt[*i] == '?')
		tmp->args = ft_strdup("?");
	else if (ft_isalpha(prompt[*i]))
	{
		while (ft_isprint(prompt[*i]) || ft_isdigit(prompt[*i]))
			(*i)++;
	}
	tlistadd_back(tokens, tmp);
}

void	lexer_pipe(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	int 	j;

	j = *i;
	while (!ft_strchr(" \t$<>|;", prompt[(*i)]))
		(*i)++;
	tmp = tlistnew("|", PIPE, NULL);
	tmp->args = ft_substr(prompt, j, *i - j);
	tlistadd_back(tokens, tmp);
}
