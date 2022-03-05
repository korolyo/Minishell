/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:37 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:16:39 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_error(char *cmd)
{
	printf("minishell: %s: command not found\n", cmd);
	return (1);
}

int	ft_clear_path_list(char ***path_list)
{
	int	index;

	index = 0;
	while (path_list[0][index] != NULL)
	{
		free(path_list[0][index]);
		index++;
	}
	free(path_list[0]);
	return (0);
}

//if id == 0: SHLVL--; if id == 1: SHLVL++
int	ft_change_lvl(t_list **var_list, int id)
{
	int		lvl;
	char	*new_value;
	t_list	*tmp_list;
	t_var	*tmp_var;

	tmp_list = ft_find_var(var_list, "SHLVL");
	tmp_var = (t_var *)tmp_list->content;
	lvl = ft_atoi(tmp_var->value);
	if (id == 0)
		new_value = ft_itoa(lvl - 1);
	if (id == 1)
		new_value = ft_itoa(lvl + 1);
	if (ft_chng_var(var_list, "SHLVL", new_value, 1) == 0)
		return (-1);
	free(new_value);
	return (lvl);
}

int	ft_add_status(t_list **var_list, int status)
{
	char	*new_value;

	new_value = ft_itoa(status);
	if (ft_chng_var(var_list, "?", new_value, 1) == 0)
		return (0);
	free(new_value);
	return (1);
}
