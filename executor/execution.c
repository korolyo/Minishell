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

int	ft_wait_pid(int n)
{
	int i;
	int status;


	i = 0;
	while (i < n)
	{
		wait(&status);
		if (WIFEXITED(status) && status != 0)
			g_exit_status = 127;
		i++;
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

int	ft_clear_execution(char **path_list, char *tmp_path, char *executor_path)
{
	ft_clear_arr(path_list);
	free(tmp_path);
	free(executor_path);
	return (1);
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
		close_pipes(misc->fdpipe, misc->cmd_count);
		if (execve(path, tokens->cmd, NULL))
			ft_cmd_error(tokens->cmd[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell");
	ft_restore_fd(tmp_in, tmp_out);
	return (1);
}
