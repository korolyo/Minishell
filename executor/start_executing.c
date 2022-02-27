#include "minishell.h"

int ft_execution(t_tlist *tokens, t_list **var_list, t_misc *misc)
{
	char **path_list;
	char *executor_path;
	char *tmp_path;
	char *tmp_path2;

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

int ft_start_execution(t_tlist *tokens, t_list **var_list, t_misc *misc)
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
	if (ft_strchr(tokens->cmd[0], '=') != NULL)
		return (ft_check_if_var(tokens->cmd, var_list));
	while (++index < 7)
	{
		if (!(strncmp(tokens->cmd[0], builtins[index].cmd, 7)))
		{
			if (tokens->fdin != -2 || tokens->fdout != -2)
				redir_id = ft_redirection(tokens, &tmp_in, &tmp_out);
			index = builtins[index].f_cmd(tokens->cmd, var_list);
			if (redir_id == 1)
				ft_restore_fd(tmp_in, tmp_out);
			if (misc->num_of_pipes != 0)
				pipe_switch(tokens, misc);
			return (index);
		}
	}
	if (index == 7) //Обработка встроенных файлов
	{
		if (ft_execution(tokens, var_list, misc) == 0)
		{
			ft_add_status(var_list, 127);
			return (ft_cmd_error(tokens->cmd[0]));
		}
	}
	return (1);
}

int ft_start(t_tlist *tokens, t_list **var_list)
{
	t_misc	misc;

	init_misc(&misc, tokens);
	misc.fdpipe = pipes(&misc);
	cmd_kind(tokens);
	while (tokens)
	{
		ft_start_execution(tokens, var_list, &misc);
		misc.i++;
		tokens = tokens->next;
	}
	return (0);
}

void	init_misc(t_misc *misc, t_tlist *tokens)
{
	misc->cmd_count = find_cmd_num(tokens);
	misc->i = 0;
	misc->num_of_pipes = tokens->pipes;
	misc->fdpipe = NULL;
}
