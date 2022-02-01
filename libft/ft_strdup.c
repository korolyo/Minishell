/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:04:12 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:04:18 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		l;
	char	*dest;

	l = ft_strlen(src);
	dest = malloc(sizeof(*src) * (l + 1));
	if (dest == ((void *)0))
		return (((void *)0));
	l = 0;
	while (src[l])
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = src[l];
	return (dest);
}
