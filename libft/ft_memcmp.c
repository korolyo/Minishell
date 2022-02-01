/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:01:09 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:01:10 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	int				comparestatus;

	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	comparestatus = 0;
	if (s1 == s2)
		return (0);
	while (n--)
	{
		if (*p != *q)
		{
			comparestatus = *p - *q;
			break ;
		}
		p++;
		q++;
	}
	return (comparestatus);
}
