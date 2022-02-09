/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:07:13 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:07:21 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
//	unsigned char		*sub;
//	unsigned char		*str;
//	size_t				slen;
//
//	slen = ft_strlen(s);
//	if (start + len > slen && start < slen)
//		len = slen - start;
//	else if (start >= slen)
//		len = 0;
//	sub = (unsigned char *)ft_calloc((len + 1), sizeof(char));
//	if (sub == ((void *)0))
//		return ((void *)0);
//	str = sub;
//	while (len > 0)
//	{
//		*sub = *(s + start);
//		sub++;
//		s++;
//		len--;
//	}
//	printf("substr1 = %s\n", str);
//	return ((char *)str);
	char	*new_s;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (start < ft_strlen(s) && len > ft_strlen(s))
		len = ft_strlen(s) - start;
	new_s = malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, &s[start], len + 1);
	printf("substr1 = %s\n", new_s);
	return (new_s);
}
