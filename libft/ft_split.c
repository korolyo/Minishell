/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:02:51 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:03:41 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//
//#include "libft.h"
//
//static int	count_words(char const *s, char c)
//{
//	int		count;
//	size_t	flag;
//	size_t	i;
//
//	count = 0;
//	flag = 1;
//	i = 0;
//	while (s[i] != '\0')
//	{
//		if (s[i] == c)
//			flag = 1;
//		else if (flag)
//		{
//			count++;
//			flag = 0;
//		}
//		i++;
//	}
//	return (count);
//}
//
//void	*ft_free_all_split_alloc(char **split, size_t elts)
//{
//	size_t	i;
//
//	i = 0;
//	while (i < elts)
//	{
//		free(split[i]);
//		i++;
//	}
//	free(split);
//	return (NULL);
//}
//
//static void	*ft_split_range(char **split, char const *s,
//							   t_split_next *st, t_split_next *lt)
//{
//	split[lt->length] = ft_substr(s, st->start, st->length);
//	if (!split[lt->length])
//		return (ft_free_all_split_alloc(split, lt->length));
//	lt->length++;
//	return (split);
//}
//
//static void	*ft_split_by_char(char **split, char const *s, char c)
//{
//	size_t			i;
//	t_split_next	st;
//	t_split_next	lt;
//
//	i = 0;
//	lt.length = 0;
//	lt.start = 0;
//	while (s[i])
//	{
//		if (s[i] == c)
//		{
//			st.start = lt.start;
//			st.length = (i - lt.start);
//			if (i > lt.start && !ft_split_range(split, s, &st, &lt))
//				return (NULL);
//			lt.start = i + 1;
//		}
//		i++;
//	}
//	st.start = lt.start;
//	st.length = (i - lt.start);
//	if (i > lt.start && i > 0 && !ft_split_range(split, s, &st, &lt))
//		return (NULL);
//	split[lt.length] = 0;
//	return (split);
//}
//
//char	**ft_split(char const *s, char c)
//{
//	char	*str;
//	char	**res;
//	int		count;
//
//	count = count_words(s, c);
//	str = (char *)s;
//	while (*str == c)
//		str++;
//	res = (char **) ft_calloc(sizeof(s), (count + 1));
//	if (res == NULL)
//		return (NULL);
//	if (!ft_split_by_char(res, s, c))
//		return (NULL);
//	return ((char **)res);
//}
//

#include "libft.h"

void	*ft_abort(char ***arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
	{
		free(arr[0][i]);
		i++;
	}
	free(arr);
	return (NULL);
}

size_t	get_len(char *str, char c, size_t *i)
{
	size_t	len;
	size_t	j;

	len = 0;
	j = *i;
	while (str[j] != c && str[j] != '\0')
	{
		len++;
		j++;
	}
	*i = j;
	return (len);
}

char	**get_str(char ***res, char **str, char c, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;
	char	*dup;

	i = 0;
	j = 0;
	dup = *str;
	while (j < size - 1)
	{
		while (dup[i] == c)
			i++;
		start = i;
		len = get_len(dup, c, &i);
		res[0][j] = (char *)malloc(sizeof(char) * len + 1);
		if (!res[0][j])
			return (ft_abort(res, size));
		ft_strlcpy(res[0][j], &dup[start], len + 1);
		j++;
	}
	res[0][j] = NULL;
	return (*res);
}

size_t	get_arrlen(char const *s, char c)
{
	size_t	i;
	size_t	len;

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

char	**ft_split(char const *str, char c)
{
	char	**result;
	size_t	size;
	char	*s;

	size = 0;
	s = (char *)str;
	if (!s)
		return (NULL);
	size = get_arrlen(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	return (get_str(&result, &s, c, size + 1));
}