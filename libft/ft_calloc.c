/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:56:51 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 21:57:02 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
	{
		size = 1;
		nmemb = size;
	}
	p = (void *)malloc(nmemb * size);
	if (NULL == p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}
