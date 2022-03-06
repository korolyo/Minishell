/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:18 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:20 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_list(t_list **var_list) //TODO убрать эту функцию, она для дебага
{
	t_list	*tmp;
	t_var	*var;

	tmp = *var_list;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		printf("%s\n", var->name);
		tmp = tmp->next;
	}
}

void	ft_print_export(char **sorted_env, t_list **var_list, int len)
{
	t_list	*tmp;
	t_var	*tmp_var;
	int		i;

	i = 0;
	while (sorted_env[i] != NULL)
	{
		if (sorted_env[i][0] == '_' && sorted_env[i][1] == '\0')
			i++;
		tmp = ft_find_var(var_list, sorted_env[i]);
		tmp_var = (t_var *)tmp->content;
		printf("declare -x %s", tmp_var->name);
		if (tmp_var->value != NULL)
			printf("=\"%s\"", tmp_var->value);
		printf("\n");
		i++;
	}
	i = 0;
	while (i < len)
	{
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}

int	ft_sort(char **sorted_name, t_list **var_list, int num)
{
	char	*tmp;
	int		top;
	int		seek;

	top = 0;
	seek = 0;
	while (top < num - 1 && sorted_name[top] != NULL)
	{
		seek = top + 1;
		while (seek < num && sorted_name[seek] != NULL)
		{
			if (ft_strncmp(sorted_name[top], sorted_name[seek], 255) > 0)
			{
				tmp = sorted_name[top];
				sorted_name[top] = sorted_name[seek];
				sorted_name[seek] = tmp;
			}
			seek++;
		}
		top++;
	}
	ft_print_export(sorted_name, var_list, num);
	return (1);
}

int	ft_sort_env(t_list **var_list, int len)
{
	char	**sorted_name;
	char	*name;
	int		count;
	t_list	*tmp_list;
	t_var	*tmp_var;

	count = 0;
	len = 0;
	tmp_list = *var_list;
	sorted_name = malloc(sizeof(char *) * (ft_lstsize(tmp_list) + 1));
	while (tmp_list)
	{
		tmp_var = (t_var *)tmp_list->content;
		if (tmp_var->is_exported != 0)
		{
			name = malloc(sizeof(char) * (ft_strlen(tmp_var->name) + 1));
			ft_strlcpy(name, tmp_var->name, ft_strlen(tmp_var->name) + 1);
			sorted_name[count] = name;
			count++;
		}
		tmp_list = tmp_list->next;
	}
	sorted_name[count] = NULL;
	ft_sort(sorted_name, var_list, count);
	return (1);
}

int	ft_export_var(t_list **var_list, char *args, t_var *tmp)
{
	t_list	*tmp_list;
	t_var	*tmp_var2;

	ft_make_var(args, tmp);
	tmp_list = ft_find_var(var_list, tmp->name);
	if (tmp_list != NULL)
		tmp_var2 = (t_var *)tmp_list->content;
	if (tmp_list && tmp_var2->is_exported == 0)
	{
		if (tmp->value != NULL)
			return (ft_chng_var(var_list, tmp->name, tmp->value, 1));
		return (ft_chng_var(var_list, tmp->name, tmp_var2->value, 1));
	}
	if (!tmp_list && ft_check_var(tmp->name, "export"))
	{
		if (tmp->value)
			ft_save_var(var_list, args, 1);
		else
			ft_save_var(var_list, args, -1);
	}
	return (1);
}

int	ft_export(char **args, t_list **var_list)
{
	int		i;
	t_var	*tmp;

	i = 1;
	tmp = malloc(sizeof(t_var));
	if (!tmp)
		return (1);
	if (args[1] == NULL)
	{
		ft_sort_env(var_list, 0);
		return (1);
	}
	while (args[i] != NULL)
	{
		ft_export_var(var_list, args[i], tmp);
		i++;
		free(tmp);
	}
	return (1);
}
