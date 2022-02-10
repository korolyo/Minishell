#include "minishell.h"

int ft_echo(char **args)
{
	int flag;
	int index;
	int len;

	flag = 1;
	index = 1;
	len = 0;
	while (args[index++] != NULL)
		len++;
	index = 1;
	if (args[index] != NULL)
		flag = ft_strncmp(args[index], "-n", 2);
	if (flag == 0)
	{
		index++;
		len--;
	}
	while (args[index++] != NULL)
	{
		printf("%s", args[index]);
		if (len > 1)
			printf(" ");
		len--;
	}
	if (flag != 0)
		printf("\n");
	return (1); //успешное завершение
}

char	*ft_prev_dir(char *pwd_path) //возможно, не потребуется надо тестить
{
	int		index;
	int		last_slash;

	index = 0;
	while (pwd_path[index] != '\0')
	{
		if (pwd_path[index] == '/')
			last_slash = index;
		index++;
	}
	return (ft_substr(pwd_path, 0, ft_strlen(pwd_path) - last_slash - 3));
}

//попроверять хорошо эту функцию
int ft_cd(char **args)
{
	char	*prev_dir;

	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell");
			return (1);
		}
		return (1);
	}
	if (!(ft_strncmp(args[1], ".", 2)))
		return (1);
	if (!(ft_strncmp(args[1], "..", 3)))
	{
		prev_dir = ft_prev_dir(getenv("PWD"));
		if (!prev_dir)
			return (0);
		if (chdir(prev_dir) != 0)
		{
			free(prev_dir);
			return (0);
		}
		free(prev_dir);
		return (1); //успешное завершение
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			printf("minishell: cd: %s: %s\n", args[1], strerror(ENOENT));
			return (1);
		}
	}
	return (1); //успешное завершение
}

int		ft_pwd(char **args) //эта, вроде, готова
{
	char	dir[MAX_DIRNAME];

	(void)args;
	if (!getcwd(dir, MAX_DIRNAME))
		return (0); //ошибка
	printf("%s\n", dir);
	return (1); //успешное завершение
}
int		ft_export( char **args)
{
	(void)args;
	printf("ft_export\n");
	return(0);
}
int		ft_unset(char **args)
{
	(void)args;
	printf("ft_unset\n");
	return(0);
}
int		ft_env(char **args)
{
	int	index;
	extern char **environ;

	index = 0;
	(void)args;
	while (environ[index] != NULL)
	{
		printf("%s\n", environ[index]);
		index++;
	}
	return (1); //успешное завершение
}

int ft_exit(char **args)
{
	(void)args;
	printf("exit\n");
	return (0);
}