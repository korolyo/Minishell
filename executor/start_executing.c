#include "minishell.h"

int ft_execution(char **args, t_list **var_list)
{
	char **path_list;
	char *executor_path;
	char *tmp_path;
	char *tmp_path2;

	tmp_path = NULL;
	executor_path = NULL;
	path_list = ft_parse_path(var_list);
	if (!path_list)
		return (0); //ошибка
	tmp_path2 = ft_find_path(path_list, args[0]);
	if (tmp_path2 == NULL)
		executor_path = args[0];
	else
		ft_join_path(args[0], tmp_path, path_list, &executor_path);
	if (ft_add_status(var_list, ft_execute_cmd(executor_path, args)) == 0)
		return (0); //ошибка
	ft_clear_path_list(&path_list);
	free(tmp_path);
	free(executor_path);
	return (1); // успешное завершение
}

int ft_check_if_var(char **args, t_list **var_list)
{
	int index;

	index = 0;
	while (args[index] != NULL)
	{
		if (ft_strchr(args[index], '=') == NULL)
			return (ft_cmd_error(args[index]));
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

int ft_start_execution(t_btree *ast, t_list **var_list)
{
	int				index;
	int 			tmp_in;
	int 			tmp_out;
	int 			redir_id;
	static t_cmd	builtins[] = {
			{"echo", ft_echo},
			{"cd", ft_cd},
			{"pwd", ft_pwd},
			{"export", ft_export},
			{"unset", ft_unset},
			{"env", ft_env},
			{"exit", ft_exit}
	};

	tmp_in = 0;
	tmp_out = 0;
	index = -1;
	redir_id = 0;
	if (ft_strchr(ast->value[0], '=') != NULL)
		return (ft_check_if_var(ast->value, var_list));
	if (ast->fdin != -1 || ast->fdout != -1)
		redir_id = ft_redirection(ast, &tmp_in, &tmp_out);
	while (++index < 7)
	{
		if (!(strncmp(ast->value[0], builtins[index].cmd, 7)))
		{
			index = builtins[index].f_cmd(ast->value, var_list);
			if (redir_id == 1)
				ft_restore_fd(tmp_in, tmp_out);
			return (index);
		}
	}
	if (index == 7)
	{
		if (ft_execution(ast->value, var_list) == 0)
		{
			ft_add_status(var_list, 127);
			return (ft_cmd_error(ast->value[0]));
		}
		if (redir_id == 1)
			ft_restore_fd(tmp_in, tmp_out);
	}
	return (1);
}

t_btree *ft_start(t_btree *ast, t_list **var_list)
{
	if (ast)
	{
		ft_start(ast->left, var_list);
		if (ast->type == CMD)
		{
			printf ("fd_in %d\nfd_out %d\n", ast->fdin, ast->fdout);
			ft_start_execution(ast, var_list);
		}
		ft_start(ast->right, var_list);
		return (ast);
	}
	return (NULL);
}
