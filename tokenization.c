/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
<<<<<<< HEAD
/*   tokenization.c                                     :+:      :+:    :+:   */
=======
/*   parsing.c                                          :+:      :+:    :+:   */
>>>>>>> aac3de6956a0406042df3c0d7ac8715c229f056e
=======
/*   parsing.c                                          :+:      :+:    :+:   */
=======
/*   tokenization.c                                     :+:      :+:    :+:   */
>>>>>>> ebce6a8... preparsing is done
>>>>>>> 73c8c19... preparsing is done
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenization(t_tlist *tokens, char *prompt)
{
	int		i;
	int		j;

	i = -1;
	while (prompt[++i])
	{
		if (is_key(prompt[i]))
		{
			j = i;
			while (is_key(prompt[i]))
				i++;
<<<<<<< HEAD
<<<<<<< HEAD
			tokens->cmd = ft_strdup(prompt + i - j);
=======
			tokens->token = ft_strdup(prompt + i - j);
>>>>>>> aac3de6956a0406042df3c0d7ac8715c229f056e
=======
			tokens->token = ft_strdup(prompt + i - j);
=======
			tokens->cmd = ft_strdup(prompt + i - j);
>>>>>>> ebce6a8... preparsing is done
>>>>>>> 73c8c19... preparsing is done
		}
		if (prompt[i] != ' ' || prompt[i] != '\\'|| prompt[i] != '|'
			|| prompt[i] != ';' || prompt[i] != '\t' || prompt[i] != '\n')
			break ;
		if (prompt[i] == '>' || prompt[i] == '<')
			tokens->type = REDIR;
		if (prompt[i] == '-')
		{
			j = i;
			while (ft_isalnum(prompt[i]))
				i++;
			tokens->args = ft_strdup(prompt + i - j);
		}
	}
}