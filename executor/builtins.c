#include "minishell.h"

int ft_echo(char **args) //вроде, отрабатывает норм, но что-то не то приходит
// в args + больше 25 строк
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

int		ft_pwd(char **args) //эта, вроде, готова
{
	char	dir[MAX_DIRNAME];

	(void)args;
	if (!getcwd(dir, MAX_DIRNAME)) //работает нормально само. Но pwd в env не
		// меняется
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