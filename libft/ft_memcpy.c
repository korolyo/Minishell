/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:01:18 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:01:21 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	unsigned const char	*psource;

	pdest = (unsigned char *)dest;
	psource = (unsigned const char *)src;
	if ((pdest == NULL) && (psource == NULL))
		return (NULL);
	while (n)
	{
		*(pdest++) = *(psource++);
		n--;
	}
	return (dest);
}
