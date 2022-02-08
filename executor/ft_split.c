//временный файл для execution.c
#include "header.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstr)
	{
		while (i < ft_strlen(s1))
		{
			newstr[i] = s1[i];
			i++;
		}
		while (j < ft_strlen(s2))
		{
			newstr[i] = s2[j];
			i++;
			j++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!(dst == NULL || src == NULL))
	{
		if (dstsize != 0)
		{
			while (i < (dstsize - 1) && src[i] != '\0')
			{
				dst[i] = src[i];
				i++;
			}
			dst[i] = '\0';
		}
		return (ft_strlen(src));
	}
	return (0);
}

static void	*ft_abort(char ***arr, size_t size)
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

static size_t	get_len(char *str, char c, size_t *i)
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

static char	**get_str(char ***res, char **str, char c, size_t size)
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

static size_t	get_arrlen(char const *s, char c)
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

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	size;
	char *str;

	size = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	size = get_arrlen(str, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (NULL);
	return (get_str(&result, &str, c, size + 1));
}


