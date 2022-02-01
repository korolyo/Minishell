/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:58:25 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 21:58:33 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strnumber(int numlen, int n)
{
	char	*number;

	number = (char *)ft_calloc(sizeof(char), numlen + 1);
	if (number == NULL || numlen > 11)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		number[0] = '-';
	}
	if (n == 0)
		number[0] = '0';
	while (n > 0)
	{
		number[numlen - 1] = n % 10 + '0';
		n = n / 10;
		numlen--;
	}
	return ((char *) number);
}

char	*ft_itoa(int n)
{
	char	*number1;
	int		numlen;
	int		k;

	numlen = 0;
	k = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		if (n < 0)
			numlen++;
		while (k != 0)
		{
			k = k / 10;
			numlen++;
		}
		if (n == 0)
			numlen++;
	}
	number1 = strnumber(numlen, n);
	return ((char *)number1);
}
