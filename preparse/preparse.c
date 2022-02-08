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

char *str_delete_part(char *prompt, int start, int end, int flag_mid)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(prompt, 0, start);
	tmp2 = NULL;
	if (flag_mid != DELETE_MID)
	{
		tmp2 = ft_substr(prompt, start + 1, end - start - 1);
		tmp = ft_strjoin(tmp, tmp2);
		free(tmp2);
	}
	tmp3 = ft_substr(prompt, end + 1, ft_strlen(prompt) - end - 1);
//	printf("tmp3 = |%s|\n", tmp3);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	return (tmp);
}

char	*preparse_delim(char *prompt, int i)
{
	char	*tmp;
	char 	*tmp2;
	int 	j;

	tmp = prompt;
	while (tmp[i])
	{
		if ((ft_strchr(" \t", tmp[i]) && i == 0)
			|| (i != 0 && ft_strchr(" \t",tmp[i])
			&& (ft_strchr(" \t", tmp[i + 1]) || tmp[i + 1] == '\0')))
		{
			j = i;
			while (ft_strchr(" \t", tmp[i]) && tmp[i])
			{
//				printf("%d - j %d - i\n", j, i);
				i++;
				if (tmp[i] == '\0' || j == 0)
					j--;
			}
			tmp2 = str_delete_part(tmp, j + 1, i - 1, DELETE_MID);
//			printf("tmp2 == |%s|\n", tmp2);
			tmp = tmp2;
			i = -1;
		}
		i++;
	}
	return (tmp);
}

int	preparse_quotes(char *prompt, int i)
{
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			if (!(ft_strchr(prompt + i + 1, '\'')))
				return (0);
		}
		if (prompt[i] == '\"')
		{
			if (!(ft_strchr(prompt + i + 1, '\"')))
				return (0);
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
	/*
	 * Cases:	два пайпа
	*/
	int		i;
	char	*tmp;

	i = -1;
	tmp = prompt;
	while (tmp[++i])
	{
		if (tmp[i] == ' ' || tmp[i] == '\t')
			tmp = preparse_delim(tmp, i);
		if (!(preparse_redir(tmp, i)))
		{
			tmp = ft_strdup("Minishell: syntax error with redir symbol");
			break ;
		}
		if (!(preparse_quotes(tmp, i)))
		{
			tmp = ft_strdup("Error: No unmatched quotes");
			break ;
		}
//		if (!(preparse_pipe(tmp, i)))
//		{
//			tmp = ft_strdup("Error: Unclosed Pipe");
//			break ;
//		}
	}
	free(prompt);
//	printf("tmp prep = %s\n", tmp);
	return (tmp);
}
