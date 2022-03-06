/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:47 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:16:50 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_pid(pid_t pid)
{
	int		status;
	pid_t	wpid;

	wpid = 0;
	while (1)
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == -1)
		{
			perror("WAIT_PID");
			return (0);
		}
		if (WIFSIGNALED(status))
			status = 130;
		else
			status = WEXITSTATUS(status);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return (status);
	}
	return (status);
}

int	ft_execute_cmd(char *path, t_tlist *tokens, t_misc *misc, char **envp)
{
	pid_t	pid;
	int		status;
	int		redir_id;
	int		tmp_in;
	int		tmp_out;

	status = 0;
	redir_id = 0;
	(void)misc;
	if ((tokens->fdin != -2 || tokens->fdout != -2) && !access(path, 00))
		redir_id = ft_redirection(tokens, &tmp_in, &tmp_out);
	pid = fork();
	if (pid && !tokens->stop_word)
		catch_heredoc_sig();
	if (pid == 0)
	{
//		if (tokens->stop_word)
//			here_doc_input(tokens);
//		if (misc->num_of_pipes > 0)
//			pipe_switch(tokens, misc);
//		if (misc->num_of_pipes > 0 || tokens->stop_word)
//			ft_redirection(tokens, &tmp_in, &tmp_out);
//		close_pipes(misc->fdpipe, misc->cmd_count);

		if (execve(path, tokens->cmd, envp))
			ft_cmd_error(tokens->cmd[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
//		if (misc->fdpipe)
//			close_pipes(misc->fdpipe, misc->cmd_count);
		status = ft_wait_pid(pid);
	}
	if (redir_id == 1)
		ft_restore_fd(tmp_in, tmp_out);
	return (status);
}

char	*ft_find_path(char **path_list, char *executor_name)
{
	DIR				*dir;
	struct dirent	*ent;
	int				index;

	index = 0;
	while (path_list[index] != NULL)
	{
		dir = opendir(path_list[index]);
		if (dir != NULL)
		{
			ent = readdir(dir);
			while (ent != NULL)
			{
				if (!ft_strncmp(ent->d_name, executor_name, MAX_FILENAME))
				{
					if (closedir(dir) != 0)
						return (NULL);
					return (path_list[index]);
				}
				ent = readdir(dir);
			}
		}
		index++;
	}
	return (NULL);
}

char	**ft_parse_path(t_list **var_list, char *cmd)
{
	const char	*path;
	char		**path_list;
	t_list		*tmp_list;
	t_var		*tmp_var;

	tmp_list = ft_find_var(var_list, "PATH");
	if (!tmp_list)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		return (NULL);
	}
	tmp_var = (t_var *)tmp_list->content;
	path = tmp_var->value;
	path_list = ft_split(path, ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

int	ft_join_path(char *args, char *tmp_path, char **path_list, char **exec_path)
{
	tmp_path = ft_strjoin("/", &args[0]);
	if (!tmp_path)
	{
		ft_clear_arr(path_list);
		return (0);
	}
	*exec_path = ft_strjoin(ft_find_path(path_list, args), tmp_path);
	if (!*exec_path)
	{
		free(path_list);
		free(tmp_path);
		return (0);
	}
	return (1);
}
