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
	g_exit_status = 127;
	return (0);
}

int	ft_clear_arr(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
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
	if (!tmp_list)
		return (1);
	tmp_var = (t_var *)tmp_list->content;
	lvl = ft_atoi(tmp_var->value);
	if (id == 0)
		new_value = ft_itoa(lvl - 1);
	if (id == 1)
		new_value = ft_itoa(lvl + 1);
	if (ft_chng_var(var_list, "SHLVL", new_value, 1) == 0)
		return (-1);
	return (lvl);
}

int	ft_add_status(t_list **var_list)
{
	char	*new_value;

	new_value = ft_itoa(g_exit_status);
	ft_chng_var(var_list, "?", new_value, 0);
	return (1);
}

char	**ft_make_env(t_list **var_list)
{
	char	**env_list;
	char	*tmp_value;
	int		count;
	t_list	*tmp_list;
	t_var	*tmp_var;

	count = 0;
	tmp_list = *var_list;
	env_list = malloc(sizeof(char *) * (ft_lstsize(tmp_list)));
	while (tmp_list)
	{
		tmp_var = (t_var *)tmp_list->content;
		if (tmp_var->is_exported == 1)
		{
			tmp_value = ft_strjoin(tmp_var->name, "=");
			env_list[count] = ft_strjoin(tmp_value, tmp_var->value);
			free(tmp_value);
			count++;
		}
		tmp_list = tmp_list->next;
	}
	env_list[count] = NULL;
	return (env_list);
}
