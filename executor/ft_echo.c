/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:07 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:10 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(char *str, int *len, int *index)
{
	printf("%s", str);
	if (*len > 1)
		printf(" ");
	*len = *len - 1;
	*index = *index + 1;
}

int	ft_echo(char **args, t_list **var_list)
{
	int	flag;
	int	index;
	int	len;

	(void)var_list;
	flag = 1;
	index = 1;
	len = 0;
	while (args[index++] != NULL)
		len++;
	index = 1;
	if (args[index] != NULL)
		flag = ft_strncmp(args[index], "-n", 2);
	if (flag == 0)
	{
		index++;
		len--;
	}
	while (args[index] != NULL)
		ft_print_echo(args[index], &len, &index);
	if (flag != 0)
		printf("\n");
	return (1);
}
