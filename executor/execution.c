#include "minishell.h"

int	ft_wait_pid(pid_t pid)
{
	int	status;
	pid_t wpid;

	wpid = 0;
	while (wpid != -1)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (wpid == -1)
		{
			//perror("WAIT_PID");
			return (0);
		}
		if (WIFSIGNALED(status))
			status = 130;
		else
			status = WEXITSTATUS(status);
	}
	return (status);
}

int ft_execute_cmd(char *path, char **args)
{
	pid_t	pid;
	int		status;

	printf("args[0] = %s\n", args[0]);
	printf("args[1] = %s\n", args[1]);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, NULL))
			ft_cmd_error(args[0]); //bash: kwdf: command not found
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("minishell"); // ошибка при форкинге
	else
	{
		status = ft_wait_pid(pid);
//		do
//		{
//			wpid = waitpid(pid, &status, WUNTRACED);
//		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}

char *ft_find_path(char **path_list, char *executor_name)
{
	DIR				*dir;
	struct dirent	*ent;
	int 			index;

	index = 0;
	while (path_list[index] != NULL)
	{
		dir = opendir(path_list[index]);
		if (dir != NULL)
		{
			while ((ent = readdir(dir)) != NULL)
			{
				if (!ft_strncmp(ent->d_name, executor_name, MAX_FILENAME))
				{
					if (closedir(dir) != 0)
						return (NULL);
					return (path_list[index]);
				}
			}
		}
//		printf("closedir = %d\n", closedir(dir)); сегается на закрытии директории, может, вообще это убрать
//		if (closedir(dir) != 0)
//			return (NULL);
		index++;
	}
	return (NULL);
}

char **ft_parse_path(t_list **var_list)
{
	const char *path;
	char **path_list;
	t_list	*tmp_list;
	t_var	*tmp_var;

	tmp_list = ft_find_var(var_list, "PATH");
	tmp_var = (t_var *)tmp_list->content;
	path = tmp_var->value;
	path_list = ft_split(path, ':');
	if (!path_list)
		return (NULL); //ошибка
	return (path_list);
}

int ft_execution(char **args, t_list **var_list)
{
	char **path_list;
	char *executor_path;
	char *tmp_path;
	char *tmp_path2;

	(void)var_list;
	path_list = ft_parse_path(var_list);
	if (!path_list)
		return (0); //ошибка
	tmp_path = ft_strjoin("/", args[0]);
	if (!tmp_path)
	{
		free(path_list);
		return (0); //ошибка
	}
	tmp_path2 = ft_find_path(path_list, args[0]);
	executor_path = ft_strjoin(tmp_path2, tmp_path);
	if (!executor_path)
	{
		free(path_list);
		free(tmp_path);
		return (0); //ошибка
	}
	if (ft_add_status(var_list, ft_execute_cmd(executor_path, args)) == 0)
		return (0); //ошибка
	ft_clear_path_list(&path_list);
	free(tmp_path);
	free(executor_path);
	return (1); // успешное завершение
}


