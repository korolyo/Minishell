#include "minishell.h"

void ft_redirection(char **args, int fd_in_open, int fd_out_open, int cmd_num, t_list **var_list)
{
	//save in/out
	int tmp_in;
	int tmp_out;
	int fd_in;
	int fd_out;
	int counter;
	int fd_pipe[2];

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	counter = 1;
	//set the initial input
	if (!fd_in_open)
		fd_in=dup(tmp_in); //Use default input
	else
		fd_in = fd_in_open;
	while (counter++ < cmd_num)
	{
		//regirect input
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		//setup output
		if (counter == cmd_num - 1)
		{
			//last simple command
			if (fd_out_open)
				fd_out = fd_out_open;
			else
				//Use default output
				fd_out=dup(tmp_out);
		}
		else
		{
			//not last simple command - create pipe
			pipe(fd_pipe);
			fd_out=fd_pipe[0];
			fd_in=fd_pipe[1];
		}
		//redirect output
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		//execute cmd
		ft_start_execution(args, var_list);
	}
	//restore in out defaults
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
}


