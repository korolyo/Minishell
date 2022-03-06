/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:47 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:49 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execution(t_tlist *tokens, t_list **var_list, t_misc *misc)
{
	char	**path_list;
	char	*executor_path;
	char	*tmp_path;
	char	*tmp_path2;

	tmp_path = NULL;
	executor_path = NULL;
	path_list = ft_parse_path(var_list, tokens->cmd[0]);
	if (!path_list)
		return (1);
	tmp_path2 = ft_find_path(path_list, tokens->cmd[0]);
	if (tmp_path2 == NULL)
		executor_path = tokens->cmd[0];
	else
		ft_join_path(tokens->cmd[0], tmp_path, path_list, &executor_path);
	if (ft_add_status(var_list, ft_execute_cmd(executor_path, tokens, misc))
		== 0)
		return (0);
	ft_clear_path_list(&path_list);
	free(tmp_path);
	free(executor_path);
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

int	ft_start_execution(t_tlist *tokens, t_list **var_list, t_misc *misc)
{
	int				index;
	int				tmp_in;
	int				tmp_out;
	int				redir_id;
	static t_cmd	builtins[] = {
	{"echo",		ft_echo},
	{"cd",		ft_cd},
	{"pwd",		ft_pwd},
	{"export",	ft_export},
	{"unset",		ft_unset},
	{"env",		ft_env},
	{"exit",		ft_exit}
	};

	tmp_in = 0;
	tmp_out = 0;
	index = -1;
	redir_id = 0;
	if (ft_strchr(tokens->cmd[0], '=') != NULL)
		return (ft_check_if_var(tokens->cmd, var_list, 0));
	while (++index < 7)
	{
		if (!(strncmp(tokens->cmd[0], builtins[index].cmd, 8)))
		{
			if (misc->num_of_pipes != 0)
				pipe_switch(tokens, misc);
			if (tokens->fdin != -2 || tokens->fdout != -2)
				redir_id = ft_redirection(tokens, &tmp_in, &tmp_out);
			index = builtins[index].f_cmd(tokens->cmd, var_list);
			if (redir_id == 1)
				ft_restore_fd(tmp_in, tmp_out);
			return (index);
		}
	}
	if (index == 7)
	{
		if (ft_execution(tokens, var_list, misc) == 0)
		{
			ft_add_status(var_list, 127);
			return (ft_cmd_error(tokens->cmd[0]));
		}
	}
	return (1);
}

int	ft_start(t_tlist *tokens, t_list **var_list)
{
	t_misc	misc;

	if (!tokens)
		return (1);
	init_misc(&misc, tokens);
	if (misc.num_of_pipes > 0)
		misc.fdpipe = pipes(&misc);
	cmd_kind(tokens);
	if (tokens->cmd[0] == NULL)
		return (1);
	while (tokens)
	{
		ft_start_execution(tokens, var_list, &misc);
		misc.i++;
		tokens = tokens->next;
	}
	return (1);
}
