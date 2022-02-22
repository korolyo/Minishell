#include "minishell.h"

int	ft_wait_pid(pid_t pid)
{
	int	status;
	pid_t wpid;

	wpid = 0;
	while (1)
	{
		wpid = waitpid(pid, &status, 0);
		printf("pid = %d\n", pid);
		printf("wpid = %d\n", wpid);
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

int ft_execute_cmd(char *path, char **args)
{
	pid_t	pid;
	int		status;
	extern char	**environ;


	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, environ))
			ft_cmd_error(args[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("minishell"); // ошибка при форкинге
	else
		status = ft_wait_pid(pid);
	printf("status = %d\n", status);
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

int ft_join_path(char *args, char *tmp_path, char **path_list, char **executor_path)
{
	tmp_path = ft_strjoin("/", &args[0]);
	if (!tmp_path)
	{
		ft_clear_path_list(&path_list);;
		return (0); //ошибка
	}
	*executor_path = ft_strjoin(ft_find_path(path_list, args), tmp_path);
	if (!*executor_path)
	{
		free(path_list);
		free(tmp_path);
		return (0); //ошибка
	}
	return (1);
}
