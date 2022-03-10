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
		if (tmp_var->value != NULL && tmp_var->value[0] != '\0')
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

int	ft_pwd(char **args, t_list **var_list)
{
	t_list	*tmp_list;
	t_var	*tmp_var;
	char	*dir;

	(void)args;
	dir = NULL;
	tmp_list = ft_find_var(var_list, "PWD");
	if (!tmp_list)
	{
		printf("%s\n", getcwd(dir, 4096));
		free(dir);
		return (1);
	}
	else
	{
		tmp_var = (t_var *)tmp_list->content;
		printf("%s\n", tmp_var->value);
	}
	return (1);
}

int	error_env(void)
{
	printf("minishell: env: No such file or directory\n");
	g_exit_status = 127;
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
		return (error_env());
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
	exit(EXIT_SUCCESS);
}
