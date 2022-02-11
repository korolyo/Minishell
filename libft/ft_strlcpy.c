/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:04:46 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:04:48 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (!size)
		return (len_src);
	if (len_src + 1 < size)
		memcpy(dst, src, len_src + 1);
	else if (size != 0)
	{
		memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len_src);
}
