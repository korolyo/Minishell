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

int	ft_var_utils(t_list **var_list, char *var_name, char *new_value, int var_id)
{
	char	*var;
	char	*var1;

	var = ft_strjoin(var_name, "=");
	var1 = ft_strjoin(var, new_value);
	ft_save_var(var_list, var1, var_id);
	free(var);
	free(var1);
	return (1);
}

int	ft_check_var(char *var, char *check_cmd)
{
	int	i;

	i = 0;
	if ((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z')
		|| (var[i] == '_' && var[i + 1] != '\0'))
	{
		while (ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_'
			|| var[i] == '$' || var[i] == '\\' || var[i] == '%'
			|| var[i] == '/')
			i++;
	}
	if (var[i] != '\0')
	{
		if (check_cmd == NULL)
			return (ft_cmd_error(var));
		printf("minishell: %s: '%s': not a valid identifier\n", check_cmd, var);
		return (0);
	}
	return (1);
}

int	ft_check_if_var(char **args, t_list **var_list, int task_id)
{
	int	index;

	index = 0;
	while (args[index] != NULL)
	{
		if (ft_strchr(args[index], '=') == NULL)
		{
			if (task_id == 0)
				return (ft_cmd_error(args[index]));
			return (-1);
		}
		index++;
	}
	if (args[index] == NULL)
	{
		index = 0;
		while (args[index] != NULL)
		{
			if (!ft_save_var(var_list, args[index], 0))
				return (0);
			index++;
		}
	}
	return (1);
}

int	ft_clear_vars(t_list *var_list)
{
	t_var	*tmp_var;

	if (var_list == NULL)
		return (0);
	ft_clear_vars(var_list->next);
	if (var_list->content)
	{
		tmp_var = (t_var *)(var_list->content);
		if (tmp_var->value)
			free(tmp_var->value);
		if (tmp_var->name)
			free(tmp_var->name);
		free(tmp_var);
		tmp_var = NULL;
	}
	var_list->next = NULL;
	if (var_list)
		free(var_list);
	return (0);
}
