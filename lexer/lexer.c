/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
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

char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp)
{
	t_tlist	*tmp_cmds;
	char	*str_before;
	char	*str_after;

	str_before = ft_substr(tmp, 0, *i);
	lexer_cmd(tokens, str_before);
	tmp_cmds = *tokens;
	tmp_cmds->pipes++;
	str_after = ft_substr(tmp, *i + 1, ft_strlen(tmp) - *i);
	*i = -1;
	free(tmp);
	return (str_after);
}

char	*dollar_string(char *input, t_list **var_list)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(input);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\'')
		{
			preparse_quotes(tmp, &i);
			i--;
		}
		if (tmp[i] == '\"')
		{
			while (tmp[++i] != '\"')
				if (tmp[i] == '$')
					tmp = lexer_dollar(tmp, &i, var_list);
		}
		if (tmp[i] == '$')
			tmp = lexer_dollar(tmp, &i, var_list);
		i++;
	}
	return (tmp);
}

void	lexer(char *input, t_tlist **tokens, t_list **var_list)
{
	int		i;
	char	*cmd;

	i = -1;
	cmd = dollar_string(input, var_list);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			preparse_quotes(cmd, &i);
		if (cmd[i] == '|')
			cmd = lexer_pipe(tokens, &i, cmd);
		else if (cmd[i] == '\0')
			break ;
	}
	lexer_cmd(tokens, cmd);
}
