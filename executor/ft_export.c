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

void ft_print_export(char **sorted_name, char **sorted_value)
{
//	t_list *tmp;
//	t_var *tmp_var;
	int i;

	i = 0;
	while (sorted_name[i] != NULL)
	{
		if (*sorted_name[i] == '_')
			i++;
//		tmp = ft_find_var(var_list, sorted_env[i]);
//		tmp_var = (t_var *)tmp->content;
		printf("declare -x %s=\"%s\"\n", sorted_name[i], sorted_value[i]);
		i++;
	}
//	i = 0;
//	while (sorted_env[i] != NULL)
//	{
//		free(sorted_env[i]);
//		i++;
//	}
//	sorted_env = NULL;
}

int stsrt(char **sorted_name, char **sorted_value, int num)
{
	char *tmp;
	char *tmp2;
	int top = 0, seek = 0;

	printf("start2\n");
	while (top < num - 1)
	{
		seek = top + 1;
		while (seek < num && sorted_name[seek] != NULL)
		{
			if (ft_strncmp(sorted_name[top], sorted_name[seek], 255) > 0)
			{
				tmp = sorted_name[top];
				tmp2 = sorted_value[top];
				sorted_name[top] = sorted_name[seek];
				sorted_value[top] = sorted_value[seek];
				sorted_name[seek] = tmp;
				sorted_value[seek] = tmp2;
			}
			seek++;
//			printf("start2\n");
		}
		top++;
	}
//	int i = 0;
//	while(strings[i] != NULL)
//	{
//		printf("%s\n", strings[i]);
//		i++;
//	}
	ft_print_export(sorted_name, sorted_value);
//	i = 0;
//	while(i < num)
//	{
//		free(strings[i]);
//		i++;
//	}
//	strings = NULL;
	return (1);
}

int ft_sort_env(t_list **var_list)
{
	char	**sorted_name; /* массив для запоминания вводимых строк */
	char	**sorted_value;
	char	*name;  /* массив переменных типа указатель */
	char	*value;
	int		count = 1; /* счетчик вводимых строк */
	t_list	**tmp_list;
	t_var	*tmp_var;

	tmp_list = var_list;
	sorted_name = malloc(sizeof(char *) * ft_lstsize(*var_list));
	sorted_value = malloc(sizeof(char *) * ft_lstsize(*var_list));
	while(*tmp_list)
	{
		tmp_var = (t_var *)(*tmp_list)->content;
		if (tmp_var->is_exported != 0)
		{
			name = malloc(sizeof(char) * ft_strlen(tmp_var->name) + 1);
			value = malloc(sizeof(char) * ft_strlen(tmp_var->value) + 1);
			ft_strlcpy(name, tmp_var->name, ft_strlen(tmp_var->name) + 1);
			ft_strlcpy(value, tmp_var->value, ft_strlen(tmp_var->value) + 1);
			printf("%s\n", name);
			sorted_name[count - 1] = name;
			sorted_value[count - 1] = value;
			count++;
		}
		*tmp_list = (*tmp_list)->next;
	}
	sorted_name[count] = NULL;
	sorted_value[count] = NULL;
	printf("start2\n");
	stsrt(sorted_name, sorted_value, count);
	return (1);
	//return ();
}

int		ft_export(char **args,  t_list **var_list)
{
	if (args[1] == NULL)
	{
		ft_sort_env(var_list);
		return(1);
	}
	return(1);
}
