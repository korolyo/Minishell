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
void	lexer(char *prompt, t_tlist **tokens, t_list **var_list)
{
	int		i;
	char	*tmp;

	//	""  ''  $  '_'  |  >  >>  < <<
	i = -1;
	tmp = prompt;
	printf("in lexer....\n");
	while (tmp[++i])
	{
//		printf("i = %d, lexer = |%s|\n", i, tmp);
		if (ft_strchr(DELIM, tmp[i]))
			i++;
		if (tmp[i] == '\'' || tmp[i] == '\"')
			//экранирует все до пробела пайпа или редиректа
			tmp = lexer_quotes(tmp, &i, var_list);
		if (ft_strchr("><", tmp[i]))
			tmp = lexer_redir(tokens, tmp, i);
//		lexer_cmd(tokens, tmp, &i);
		if (tmp[i] == '$')
			tmp = lexer_dollar(tmp, &i, var_list);
		if (prompt[i] == '|')
			tmp = lexer_pipe(tokens, &i);
	}
}