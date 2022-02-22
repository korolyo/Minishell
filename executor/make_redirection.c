#include "minishell.h"
//
//void ft_redirection(int fd_in, int fd_out)
//{
//	//save in/out
//	int tmp_in;
//	int tmp_out;
//	//int fd_pipe[2];
//
//	tmp_in = dup(STDIN_FILENO);
//	tmp_out = dup(STDOUT_FILENO);
//	//set the initial input
//	if (fd_in == -1)
//		fd_in=dup(tmp_in); //Use default input
//	dup2(fd_in, STDIN_FILENO);
//	close(fd_in);
//	dup2(fd_out, STDOUT_FILENO);
//	close(fd_out);
//	//restore in out defaults
////	dup2(tmp_in, STDIN_FILENO);
////	dup2(tmp_out, STDOUT_FILENO);
////	close(tmp_in);
////	close(tmp_out);
//}
