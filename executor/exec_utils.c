////временный файл для execution.c
//#include "minishell.h"
//
//void	*ft_abort(char ***arr, size_t size)
//{
//	size_t	i;
//
//	i = 0;
//	while (i <= size)
//	{
//		free(arr[0][i]);
//		i++;
//	}
//	free(arr);
//	return (NULL);
//}
//
//size_t	get_len(char *str, char c, size_t *i)
//{
//	size_t	len;
//	size_t	j;
//
//	len = 0;
//	j = *i;
//	while (str[j] != c && str[j] != '\0')
//	{
//		len++;
//		j++;
//	}
//	*i = j;
//	return (len);
//}
//
//char	**get_str(char ***res, char **str, char c, size_t size)
//{
//	size_t	i;
//	size_t	j;
//	size_t	start;
//	size_t	len;
//	char	*dup;
//
//	i = 0;
//	j = 0;
//	dup = *str;
//	while (j < size - 1)
//	{
//		while (dup[i] == c)
//			i++;
//		start = i;
//		len = get_len(dup, c, &i);
//		res[0][j] = (char *)malloc(sizeof(char) * len + 1);
//		if (!res[0][j])
//			return (ft_abort(res, size));
//		ft_strlcpy(res[0][j], &dup[start], len + 1);
//		j++;
//	}
//	res[0][j] = NULL;
//	return (*res);
//}
//
//size_t	get_arrlen(char const *s, char c)
//{
//	size_t	i;
//	size_t	len;
//
//	i = 0;
//	len = 0;
//	if (!ft_strlen(s))
//		return (0);
//	while (s[i] != '\0')
//	{
//		if (s[i] != c && s[i] != '\0')
//		{
//			len++;
//			while (s[i] != c && s[i] != '\0')
//				i++;
//		}
//		if (s[i] == '\0')
//			break ;
//		i++;
//	}
//	return (len);
//}
