/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:06:47 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:07:35 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*s;
	size_t	i;
	size_t	j;
	size_t	tlen;

	i = 0;
	s = (char *)s1;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) != NULL && i < j)
		i++;
	while (ft_strchr(set, s1[j]) != NULL && j > 0)
		j--;
	if (j < i)
		tlen = 0;
	else
		tlen = j - i + 1;
	trimmed = ft_substr(s, i, tlen);
	return ((char *) trimmed);
}
