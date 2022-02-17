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

char	*dollar_string(char *tmp, t_list **var_list)
{
	int		i;
	char	*ret;

	i = -1;
	ret = ft_strdup(tmp);
	while (ret[++i])
	{
		if (ret[i] == '\'')
			preparse_quotes(ret, &i);
		if (ret[i] == '$')
		{
			ret = lexer_dollar(ret, &i, var_list);
			i--;
		}
	}
	free(tmp);
//	printf("ret in dollar string = |%s|\n", ret);
	return (ret);
}

void	lexer(char *prompt, t_tlist **tokens, t_list **var_list)
{
	int		i;
	int 	j;
	char	*tmp;

	j = 0;
	i = -1;
	tmp = dollar_string(prompt, var_list);
	while (tmp[++i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			preparse_quotes(tmp, &i);
		if (tmp[i] == '|')
			tmp = lexer_pipe(tokens, &i, tmp);
		if (tmp[i] == '\0')
			break;
	}
	lexer_cmd(tokens, tmp);
	free(tmp);
}
