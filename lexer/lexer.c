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
void	lexer(char *prompt, t_tlist **tokens)
{
	int		i;

	//	""  ''  $  '_'  |  >  >>  < <<
	i = -1;
	while (prompt[++i])
	{
		if (ft_strchr("DELIM", prompt[i]))
			i++;
		if (ft_strchr("\'\"", prompt[i]))
			//экранирует все до пробела пайпа или редиректа
			lexer_quotes(tokens, prompt, &i);
		if (ft_strchr("><", prompt[i]))
			lexer_redir(tokens, prompt, &i);
		if (prompt[i] >= 'a' && prompt[i] <= 'z')
			lexer_cmd(tokens, prompt, &i);
		if (prompt[i] == '$')
			lexer_env(tokens, prompt, &i);
		if (prompt[i] == '|')
			lexer_pipe(tokens, &i);
	}
}