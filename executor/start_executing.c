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
	char	**env;

	tmp_path = NULL;
	env = NULL;
	path_list = ft_parse_path(var_list, tokens->cmd[0]);
	if (!path_list)
		return (0);
	tmp_path2 = ft_find_path(path_list, tokens->cmd[0]);
	if (tmp_path2 == NULL)
		executor_path = ft_strdup(tokens->cmd[0]);
	else
		ft_join_path(tokens->cmd[0], tmp_path, path_list, &executor_path);
	env = ft_make_env(var_list);
	ft_execute_cmd(executor_path, tokens, misc, env);
	ft_clear_arr(env);
	return (ft_clear_execution(path_list, tmp_path, executor_path));
}

int	ft_start_redir(t_tlist *tokens, t_misc *misc, int *tmp_in, int *tmp_out)
{
	if (misc->num_of_pipes != 0)
		pipe_switch(tokens, misc);
	if (tokens->fdin != -2 || tokens->fdout != -2)
		return (ft_redirection(tokens, tmp_in, tmp_out));
	return (0);
}

int	ft_builings(t_tlist *tokens, t_misc *misc, t_list **var_list, int *index)
{
	int				redir_id;
	int				tmp_in;
	int				tmp_out;
	static t_cmd	builtins[] = {
	{"echo", ft_echo}, {"cd", ft_cd}, {"pwd", ft_pwd}, {"export", ft_export},
	{"unset", ft_unset}, {"env", ft_env}, {"exit", ft_exit}
	};

	if (!(strncmp(tokens->cmd[0], builtins[*index].cmd, 8)))
	{
		tmp_in = 0;
		tmp_out = 0;
		redir_id = ft_start_redir(tokens, misc, &tmp_in, &tmp_out);
		*index = builtins[*index].f_cmd(tokens->cmd, var_list);
		if (*index == 0)
			g_exit_status = 127;
		if (redir_id == 1)
			ft_restore_fd(tmp_in, tmp_out);
		return (1);
	}
	return (0);
}

int	ft_start_execution(t_tlist *tokens, t_list **var_list, t_misc *misc)
{
	int				id;
	int				index;

	index = -1;
	id = 0;
	if (ft_strchr(tokens->cmd[0], '=') != NULL)
		return (ft_check_if_var(tokens->cmd, var_list, 0));
	while (++index < 7)
	{
		id = ft_builings(tokens, misc, var_list, &index);
		if (id == 1)
			return (1);
	}
	if (index == 7)
		id = ft_execution(tokens, var_list, misc);
	if (id != 0)
		return (index);
	return (1);
}

int	ft_start(t_tlist *tokens, t_list **var_list)
{
	t_misc	misc;
	int		i;

	if (!tokens)
		return (1);
	init_misc(&misc, tokens);
	if (misc.num_of_pipes > 0)
		misc.fdpipe = pipes(&misc);
	cmd_kind(tokens);
	while (tokens)
	{
		i = ft_start_execution(tokens, var_list, &misc);
		misc.i++;
		tokens = tokens->next;
	}
	close_pipes(misc.fdpipe, misc.cmd_count);
	if (i == 7)
		ft_wait_pid(misc.cmd_count);
	if (misc.fdpipe)
		free(misc.fdpipe);
	return (1);
}
