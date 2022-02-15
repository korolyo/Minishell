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
	int 	j;
	char	*tmp;
//	char	*tmp1;

	j = 0;
	i = -1;
	tmp = ft_strdup(prompt);
	free(prompt);
//	printf("in lexer....\n");
	while (tmp[++i])
	{
		j = i;
		while (tmp[i + 1] != '|' && tmp[i])
		{
			if (tmp[i] == '\'' || tmp[i] == '\"')
			{
				tmp = lexer_quotes(tmp, &i, var_list);
				break;
			}
			if (tmp[i] == '$')
			{
				tmp = lexer_dollar(tmp, &i, var_list);
				i--;
			}
			i++;
//			printf("i = %d, lexer in while = |%s|\n", i, tmp);
		}
		if (tmp[i] == '|')
			tmp = ft_substr(tmp, j, i - j);
//		printf("i = %d, lexer before cmd = |%s|\n", i, tmp);
//		printf("tokens in lexer :");
//		print_tokens(*tokens);
		lexer_cmd(tokens, tmp);
		if (tmp[i] == '\0')
			break;
//		printf("tmp[i] = |%c|\n", tmp[i]);
//		printf("i = %d, lexer = |%s|\n", i, tmp);
		if (tmp[i] == '|')
			tmp = lexer_pipe(tokens, &i, tmp);
//		printf("i = %d, lexer = |%s|\n", i, tmp);
	}
	free(tmp);
}
