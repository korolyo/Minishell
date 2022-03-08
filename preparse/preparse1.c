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

char	*str_delete_part(char *input, int start, int end, int flag_mid)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp = ft_substr(input, 0, start);
	tmp3 = ft_substr(input, end + 1, ft_strlen(input) - end - 1);
	tmp2 = NULL;
	if (flag_mid != DELETE_MID)
		tmp2 = ft_substr(input, start + 1, end - start - 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	if (tmp4)
		free(tmp4);
	if (tmp3)
		free(tmp3);
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
	if (tmp)
		free(tmp);
	return (retu);
}
