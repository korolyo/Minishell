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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;

	new_s = NULL;
	if (start > ft_strlen(s))
		len = 0;
	if (s == NULL || len == 0)
		return (NULL);
	if (start < ft_strlen(s) && len > ft_strlen(s))
		len = ft_strlen(s) - start;
	new_s = malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, &s[start], len + 1);
	return (new_s);
}
