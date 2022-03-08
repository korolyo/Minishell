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

void	ft_start_heredoc(t_tlist *tokens, t_misc *misc, int *tmp_in, int
*tmp_out)
{
	if (tokens->stop_word)
		here_doc_input(tokens);
	if (misc->num_of_pipes > 0)
		pipe_switch(tokens, misc);
	if (misc->num_of_pipes > 0 || tokens->stop_word)
		ft_redirection(tokens, tmp_in, tmp_out);
}

int	ft_execute_cmd(char *path, t_tlist *tokens, t_misc *misc)
{
	pid_t	pid;
	int		tmp_in;
	int		tmp_out;

	ft_redirection(tokens, &tmp_in, &tmp_out);
	pid = fork();
	catch_heredoc_sig();
	if (pid == 0)
	{
		ft_start_heredoc(tokens, misc, &tmp_in, &tmp_out);
		if (execve(path, tokens->cmd, NULL))
			ft_cmd_error(tokens->cmd[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		if (misc->num_of_pipes > 0)
			close(misc->fdpipe[1]);
		g_exit_status = ft_wait_pid(pid);
	}
	ft_restore_fd(tmp_in, tmp_out);
	return (1);
}
