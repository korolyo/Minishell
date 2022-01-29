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

char	*preparse_quotes(char *prompt, int *i)
{
	int 	j;
	char	*tmp;

	j = *i;
	while (prompt[++(*i)])
		if (prompt[*i] == '\'')
			break ;
	tmp = ft_substr(prompt, 0, j - 1);
	free(prompt);
	return (tmp);
}

// Divide string from readline to lexical tokens (each token is linked list
// node:
char	*preparse(char *prompt)
{
	//незакрытая ковычка, два пайпа, две точки с запятой, незакрытый бэкслэш,
//	пайк точка запятая, команда с пайпа, команда с точки с запятой
	int		i;
	char	*tmp;

	i = -1;
	while (prompt[++i])
	{
		while (prompt[i] == ' ' || prompt[i] == '\t')
			i++;
		break;
	}
	tmp = ft_substr(prompt, i, ft_strlen(prompt) - i + 1);
	free(prompt);
	return (tmp);
}
