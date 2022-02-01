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

// Divide preparsed string from readline to lexical tokens (each token is
// linked list node):
void	lexer(char *prompt)
{

	int		i;
	int		j;
	t_tlist	*tokens;

	i = -1;
	init_lexer(prompt, tokens);
	while (prompt[++i])
	{
		if (prompt[i] == DELIM)
			next_token;
		if (prompt[i] == '\\')
			lexer_slash;
		if (prompt[i] == ';')
			lexer_semicolon;
		if (prompt[i] == '\'\"')
			lexer_prompt;
		if (ft_strchr("><", prompt[i])
			lexer_redir;

	}
}