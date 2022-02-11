/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_quotes_abort(char ***arr, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		free(arr[0][i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	get_quotes_len(char *str, char c, int *i)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (str[*i] != c && str[*i] != '\0')
	{
		j = *i;
		if (str[j] == '\'' || str[j] == '\"')
		{
			preparse_quotes(str, &j);
			len = len + (j - *i);
		}
		len++;
		(*i)++;
	}
	return (len);
}

char	**get_quotes_str(char ***res, char **str, char c, int size)
{
	int		i;
	int		j;
	int		start;
	int		len;
	char	*dup;

	i = 0;
	j = 0;
	dup = *str;
	while (j < size - 1)
	{
		while (dup[i] == c)
			i++;
		start = i;
		len = get_quotes_len(dup, c, &i);
		res[0][j] = (char *)malloc(sizeof(char) * len + 1);
		if (!res[0][j])
			return (ft_quotes_abort(res, size));
		ft_strlcpy(res[0][j], &dup[start], len + 1);
		j++;
	}
	res[0][j] = NULL;
	return (*res);
}

int	get_quotes_arrlen(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			len++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (len);
}

char	**ft_quotes_split(char const *str, char c)
{
	char	**result;
	int		size;
	char	*s;

	size = 0;
	s = (char *)str;
	if (!s)
		return (NULL);
	size = get_quotes_arrlen(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	return (get_quotes_str(&result, &s, c, size + 1));
}