/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:05:48 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:05:52 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t blen)
{
	size_t	llen;
	size_t	i;

	llen = ft_strlen(little);
	i = 0;
	if (0 == llen)
		return ((char *)big);
	while (i < blen)
	{
		if (big[0] == little[0] && (ft_strncmp(big, little, llen) == 0))
			return ((char *)big);
		if (i + llen >= blen || !*big)
			return (NULL);
		big++;
		i++;
	}
	return (NULL);
}
