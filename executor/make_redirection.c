#include "minishell.h"

void ft_restore_fd(int tmp_in, int tmp_out)
{
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
}

int ft_redirection(t_btree *ast, int *tmp_in, int *tmp_out)
{
	*tmp_in = dup(STDIN_FILENO);
	*tmp_out = dup(STDOUT_FILENO);
	if (ast->fdin == -1)
		ast->fdin=dup(*tmp_in);
	dup2(ast->fdin, STDIN_FILENO);
	close(ast->fdin);
	if (ast->fdout == -1)
		ast->fdout=dup(*tmp_out);
	dup2(ast->fdout, STDOUT_FILENO);
	close(ast->fdout);
	return (1);
}
