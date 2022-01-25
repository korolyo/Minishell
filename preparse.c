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
void	preparse(char *prompt, t_textbuf *textbuf)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (prompt[++i])
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'')
			textbuf->token[k] = preparse_quotes(prompt, &i);
	}
}
