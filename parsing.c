/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_quotes(char *str, int i)
{
	int j;

	j = i;
	while (str[++i] != ''')

}

void	parse_line(char *str)
{
//	""  ''  \  $  ;  '_'  |  >  >>  <
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ''')
			ft_quotes(str, i);
//		if (str[i] == '\"')
//			ft_doublequotes(str, i);
//		if (str[i]) == '\ ')
//			ft_whitespace(str, i);
//		if (str[i]) == '$')
//			ft_dollar(str, i);
//		if (str[i] == '\\')
//			ft_backslash(str, i);
//		if (str[i] == '\;')
//			ft_semicolon(str, i);
//		if (str[i] == '\|')
//			ft_pipe(str, i);
//		if (str[i] == '>' || str[i] == '>>' || str[i] == '<')
//			ft_redirect(str, i);
	}
}
