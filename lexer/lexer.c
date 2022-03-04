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

void	init_num(t_num *num)
{
	num = (t_num *)malloc(sizeof(t_num));
	num->i = 0;
	num->j = 0;
	num->k = 0;
}

char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp)
{
	t_tlist	*tmp_cmds;
	char	*str_before;
	char	*str_after;

	str_before = ft_substr(tmp, 0, *i);
	lexer_cmd(tokens, str_before);
	tmp_cmds = *tokens;
	tmp_cmds->pipes++;
	printf("check pipes = %d\n", (*tokens)->pipes);
	str_after = ft_substr(tmp, *i + 1, ft_strlen(tmp) - *i);
	*i = -1;
	free(tmp);
	return (str_after);
}

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
		if (ret[i] == '\"')
		{
			while (ret[++i] != '\"')
				if (ret[i] == '$')
					ret = lexer_dollar(ret, &i, var_list);
		}
		if (ret[i] == '$')
			ret = lexer_dollar(ret, &i, var_list);
	}
	free(tmp);
	return (ret);
}

void	lexer(char *prompt, t_tlist **tokens, t_list **var_list)
{
	int		i;
	char	*tmp;
	t_num	num;

	i = -1;
	tmp = dollar_string(prompt, var_list);
	init_num(&num);
	while (tmp[++i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			preparse_quotes(tmp, &i);
		if (tmp[i] == '|')
			tmp = lexer_pipe(tokens, &i, tmp);
		if (tmp[i] == '\0')
			break ;
	}
	lexer_cmd(tokens, tmp);
	free(tmp);
}
