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

char	*preparse_delim(char *prompt, int i)
{
	char	*tmp;
	char 	*tmp2;
	int 	j;

	tmp = ft_strdup(prompt);
	while (tmp[++i] != '\0')
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			preparse_quotes(tmp, &i);
		if ((tmp[i] == ' ' || tmp[i] == '\t') && i == 0)
		{
			while (tmp[i] == ' ' || tmp[i] == '\t')
				i++;
			tmp = ft_substr(prompt, i, ft_strlen(tmp) - i);
			i = -1;
		}
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
		{
			j = i;
			while (tmp[i] == ' ' || tmp[i] == '\t')
				i++;
			if (tmp[i] == '\0')
				j--;
			tmp2 = str_delete_part(tmp, j + 1, i - 1, DELETE_MID);
			tmp = ft_strdup(tmp2);
			free(tmp2);
			i = -1;
		}
	}
	free(prompt);
	return (tmp);
}

void	preparse_quotes(char const *prompt, int *i)
{
	(*i)++;
	if (prompt[(*i) - 1] == '\'')
	{
		while (prompt[*i] != '\'')
			(*i)++;
		if (prompt[*i] != '\0')
			(*i)++;
	}
	if (prompt[(*i) - 1] == '\"')
	{
		while (prompt[*i] != '\"')
			(*i)++;
		if (prompt[*i] != '\0')
			(*i)++;
	}
}

int	unmatched_quotes(char *prompt, int i)
{
	i++;
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

int preparse_redir(char *prompt, int i)
{
	if (prompt[i] == '>')
	{
		if (prompt[i + 1] == '<' || prompt[i + 1] == '\0' ||
			((prompt[i + 1] == '>' && ft_strchr("<>", prompt[i + 2]))))
			return (0);
	}
	if (prompt[i] == '<')
	{
		if (prompt[i + 1] == '>' || prompt[i + 1] == '\0' ||
			((prompt[i + 1] == '<' && ft_strchr("<>", prompt[i + 2]))))
			return (0);
	}
	return (1);
}
// Checking readline string validity:
char	*preparse(char *prompt)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!prompt)
	{
		printf("exit\n");
		return (NULL);
	}
	tmp = ft_strdup(prompt);
	if (unmatched_quotes(tmp, i) == 0)
	{
		printf("unmatched quotes\n");
		free(prompt);
		free(tmp);
		return (NULL);
	}
//	printf("in preparse\n");
	tmp = preparse_delim(tmp, i);
	while (tmp[++i])
	{
//		printf("i = %d, tmp prep = %s\n", i, tmp);
		if (!(preparse_redir(tmp, i)))
		{
			tmp = ft_strdup("Minishell: syntax error with redir symbol");
			free(prompt);
			free(tmp);
			return (NULL);
		}
		if (!(preparse_pipe(tmp, i)))
		{
			printf("Error: Unclosed Pipe\n");
			free(prompt);
			free(tmp);
			return (NULL);
		}
	}
	free(prompt);
//	printf("tmp prep = %s\n", tmp);
	return (tmp);
}
