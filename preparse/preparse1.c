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
	}
	return (1);
}

char	*str_delete_part(char *prompt, int start, int end, int flag_mid)
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
	free(prompt);
	return (tmp);
}

char	*prep_clear(char *str, char *tmp, char *prompt)
{
	if (str)
		printf("Error: %s\n", str);
	if (tmp)
		free(tmp);
	if (prompt)
		free(prompt);
	return (NULL);
}

char	*delim_str(char *prompt, int *i, char *tmp)
{
	char	*retu;
	int		j;

	j = *i;
	while ((tmp[*i] == ' ' || tmp[*i] == '\t') && tmp[*i] != '\0')
		(*i)++;
	if (j == 0)
		retu = ft_substr(prompt, *i, ft_strlen(tmp) - (*i));
	else
	{
		if (tmp[*i] == '\0')
			j--;
		retu = str_delete_part(tmp, j + 1, (*i) - 1, DELETE_MID);
	}
	(*i) = -1;
	free(prompt);
	return (retu);
}
