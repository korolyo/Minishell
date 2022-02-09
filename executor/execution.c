#include "minishell.h"
// это, вроде, хорошо работает. По крайней мере, на первый взгляд
//ВАЖНО! в случае ошибок - процесс не завершается,
// вызывающая функция получает 1 и может выводить ошибку и ждать другую команду
// возможно, стоит сделать коды ошибок (malloc и прочее и возвращать соотвествующие коды

//функция для очистки path_list, можно перенести в utils
//вроде, работает, ликс и санитайзер - утечек нет. Проверить еще раз
int	ft_clear_path_list(char ***path_list)
{
	int	index;

	index = 0;
	while (path_list[0][index] != NULL)
	{
		free(path_list[0][index]);
		index++;
	}
	free(path_list[0]);
	return (0); //успешное завершение
}

//принимает путь к исполняемому файлу и аргументы
// (?)envp - третий параметр. пока не понимаю, зачем он нужен
int ft_execute_cmd(char *path, char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, NULL))
			perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("minishell"); // ошибка при форкинге
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
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
		if (closedir(dir) != 0)
			return (NULL);
		index++;
	}
	return (NULL);
}

char **ft_parse_path()
{
	const char *path;
	char **path_list;

	path = getenv("PATH");
	path_list = ft_split(path, ':');
	if (!path_list)
		return (NULL); //ошибка
	return (path_list);
}

int ft_execution(char **args)
{
	char **path_list;
	char *executor_path;
	char *tmp_path;
	//char *args[] = {"mkdir", "my_dir", NULL};

	path_list = ft_parse_path();
	if (!path_list)
		return (0); //ошибка
	tmp_path = ft_strjoin("/", args[0]);
	if (!tmp_path)
	{
		free(path_list);
		return (0); //ошибка
	}
	executor_path = ft_strjoin(ft_find_path(path_list, args[0]), tmp_path);
	if (!executor_path)
	{
		free(path_list);
		free(tmp_path);
		return (0); //ошибка
	}
	ft_execute_cmd(executor_path, args);
	ft_clear_path_list(&path_list);
	free(tmp_path);
	free(executor_path);
	return (1); // успешное завершение
}


