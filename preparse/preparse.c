/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*preparse_delim(char *input, int i)
{
	char	*tmp;

	tmp = ft_strdup(input);
	while (tmp[++i] != '\0')
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			preparse_quotes(tmp, &i);
		if ((tmp[i] == ' ' || tmp[i] == '\t') && i == 0)
			tmp = delim_str(input, &i, tmp);
		else if ((tmp[i] == ' ' || tmp[i] == '\t') && (i != 0)
			&& (tmp[i + 1] != ' ' && tmp[i + 1] != '\t' && tmp[i + 1] != '\0'))
		{
			i++;
			if (tmp[i] == '\'' || tmp[i] == '\"')
			{
				preparse_quotes(tmp, &i);
				i--;
			}
		}
		else if (tmp[i] == ' ' || tmp[i] == '\t')
			tmp = delim_str(input, &i, tmp);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

void	preparse_quotes(char const *prompt, int *i)
{
	if (prompt[*i] == '\'')
	{
		(*i)++;
		while (prompt[*i] != '\'' && prompt[*i] != '\0')
			(*i)++;
		if (prompt[*i] != '\0')
			(*i)++;
	}
	if (prompt[*i] == '\"')
	{
		(*i)++;
		while (prompt[*i] != '\"' && prompt[*i] != '\0')
			(*i)++;
		if (prompt[*i] != '\0')
			(*i)++;
	}
}

int	unmatched_quotes(char *prompt, int i)
{
	i++;
	if (!prompt)
		return (2);
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			if (!(ft_strchr(prompt + i + 1, '\'')))
				return (0);
			break ;
		}
		if (prompt[i] == '\"')
		{
			if (!(ft_strchr(prompt + i + 1, '\"')))
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}

int	preparse_redir(char *prompt, int i)
{
	if (prompt[i] == '>')
	{
		if (prompt[i + 1] == '<' || prompt[i + 1] == '\0'
			|| ((prompt[i + 1] == '>'
					&& ft_strchr("<>", prompt[i + 2]))))
			return (0);
	}
	if (prompt[i] == '<')
	{
		if (prompt[i + 1] == '>' || prompt[i + 1] == '\0'
			|| ((prompt[i + 1] == '<'
					&& ft_strchr("<>", prompt[i + 2]))))
			return (0);
	}
	return (1);
}

char	*preparse(char *input)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = NULL;
	tmp2 = ft_strdup(input);
	if (unmatched_quotes(tmp2, i) == 0)
		return (prep_clear("Unmatched quotes", tmp, input));
	tmp = preparse_delim(tmp2, i);
	if (tmp2)
		free(tmp2);
	if (!tmp)
		return (NULL);
	if (tmp[0] == '\0')
		return (prep_clear(NULL, tmp, input));
	while (tmp[++i])
	{
		if (!(preparse_redir(tmp, i)))
			return (prep_clear("Syntax error with redir symbol", tmp, input));
		if (!(preparse_pipe(tmp, i)))
			return (prep_clear("Unclosed Pipe", tmp, input));
	}
	free(input);
	return (tmp);
}
