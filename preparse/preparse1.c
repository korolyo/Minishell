/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparse_pipe(char *prompt, int i)
{
	if (prompt[i] == '|')
	{
		if (prompt[++i] == '\0')
			return (0);
//	while (prompt[++i])
//	{
//		if (prompt[i] == '|')
//	}
	}
	return (1);
}

char *str_delete_part(char *prompt, int start, int end, int flag_mid)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(prompt, 0, start);
	tmp2 = NULL;
	if (flag_mid != DELETE_MID)
	{
		tmp2 = ft_substr(prompt, start + 1, end - start - 1);
		tmp = ft_strjoin(tmp, tmp2);
		if (tmp2)
			free(tmp2);
	}
	tmp3 = ft_substr(prompt, end + 1, ft_strlen(prompt) - end - 1);
	tmp = ft_strjoin(tmp, tmp3);
	if (tmp3)
		free(tmp3);
	return (tmp);
}
