/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:01:28 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:01:30 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	unsigned const char	*psource;

	pdest = (unsigned char *)dest;
	psource = (unsigned const char *)src;
	if ((pdest == NULL) && (psource == NULL))
		return (NULL);
	if ((psource < pdest) && (pdest < psource + n))
	{
		pdest += n;
		psource += n;
		while (n--)
		{
			*(--pdest) = *(--psource);
		}
	}
	else
	{
		while (n)
		{
			*(pdest++) = *(psource++);
			n--;
		}
	}
	return (dest);
}
