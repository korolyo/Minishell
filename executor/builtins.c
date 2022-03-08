/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:22 by acollin           #+#    #+#             */
/*   Updated: 2022/03/07 21:04:14 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_list **var_list)
{
	t_list	*tmp_list;
	t_var	*tmp_var;

	(void)args;
	tmp_list = ft_find_var(var_list, "PWD");
	tmp_var = (t_var *)tmp_list->content;
	printf("%s\n", tmp_var->value);
	g_exit_status = 0;
	return (1);
}

int	ft_env(char **args, t_list **var_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	tmp = *var_list;
	(void)args;
	if (!ft_find_var(var_list, "PATH"))
	{
		printf("minishell: env: No such file or directory\n");
		return (1);
	}
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (tmp_ptr->is_exported == 1)
		{
			printf("%s", tmp_ptr->name);
			if (tmp_ptr->value != NULL && tmp_ptr->value[0] != '\0')
				printf("=%s", tmp_ptr->value);
			printf("\n");
		}
		tmp = next;
	}
	return (1);
}

int	ft_exit(char **args, t_list **var_list)
{
	t_var		*tmp_var;
	t_list		*tmp_list;

	(void)args;
	printf("exit\n");
	tmp_list = ft_find_var(var_list, "SHLVL");
	tmp_var = (t_var *)tmp_list->content;
	if (tmp_var->value[0] == '2')
	{
		ft_clear_vars(*var_list);
		exit(EXIT_SUCCESS);
	}
	ft_change_lvl(var_list, 0);
	return (1);
}
