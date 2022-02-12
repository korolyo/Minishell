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
	char	*tmp1;

	//	""  ''  $  '_'  |  >  >>  < <<
	i = -1;
	tmp = prompt;
	printf("in lexer....\n");
	while (tmp[++i])
	{
		if (tmp[i] == '|' || tmp[i + 1] == '\0')
		{
			j = i;
			tmp1 = ft_substr(tmp, j, i);
			lexer_cmd(tokens, tmp1, &i, var_list);
			tmp = lexer_pipe(tokens, &i);
		}
	}
	printf("i = %d, lexer = |%s|\n", i, tmp);
}
