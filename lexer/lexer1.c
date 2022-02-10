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
void	lexer_quotes(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	int 	j;

	j = *i;
	if (prompt[*i] == '\'')
	{
		while (prompt[(*i)] != '\'')
			i++;
		tmp = tlistnew(QUOTES);
	}
	if (prompt[*i] == '\"')
	{
		while (prompt[(*i)] != '\"')
			i++;
		tmp = tlistnew(QUOTES);
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
		tmp = tlistnew(HERE_DOC);
		(*i)++;
	}
	else if (prompt[*i] == '>' && prompt[(*i) + 1] == '>')
	{
		tmp = tlistnew(REDIR_APPEND);
		(*i)++;
	}
	else if (prompt[*i] == '>')
		tmp = tlistnew(REDIR);
	else if (prompt[*i] == '<')
		tmp = tlistnew(REDIR_INPUT);
	(*i)++;
	while (prompt[*i] == ' ' || ft_isalpha(prompt[*i])
		|| ft_isdigit(prompt[*i]))
		(*i)++;
	if (tmp->type == REDIR || tmp->type == REDIR_APPEND ||
		tmp->type == REDIR_INPUT)
		tmp->cmd[1] = ft_substr(prompt, j, *i - j);
	tlistadd_back(tokens, tmp);
}

void	lexer_cmd(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
	char	*tmp_str;
	int 	j;
	int		count;

	j = *i;
	count = -1;
	while (!ft_strchr("$<>|", prompt[(*i)]))
		(*i)++;
	tmp = tlistnew(CMD);
//	printf("prompt = %s\n", prompt);
//	printf("i = %d j = %d\n", *i, j);
	tmp_str = ft_substr(prompt, j, *i - j);
//	printf("tmp_str = %s\n", tmp_str);
	tmp->cmd = ft_split(tmp_str, ' ');
//	while (tmp->cmd[++count])
//		printf("count = %d tlist->cmd = |%s|\n", count, tmp->cmd[count]);
//	printf("cmd check\n");

	tlistadd_back(tokens, tmp);

}

void	lexer_env(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist *tmp;
	char	*str;
	int		j;

	(*i)++;
	j = *i;
	tmp = tlistnew(ENV);
	if (!(ft_isalpha(prompt[*i])) || prompt[*i] != '?')
		tmp->cmd = NULL;
	else if (prompt[*i] == '?')
		(*i)++;
	else if (ft_isalpha(prompt[*i]))
	{
		while (ft_isprint(prompt[*i]) || ft_isdigit(prompt[*i]))
			(*i)++;
	}
	str = ft_substr(prompt, j, *i - j);
	tlistadd_back(tokens, tmp);
}

void	lexer_pipe(t_tlist **tokens, int *i)
{
	t_tlist	*tmp;

	(*i)++;
	tmp = tlistnew(PIPE);
	tlistadd_back(tokens, tmp);
}
