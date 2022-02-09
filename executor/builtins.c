

#include "minishell.h"
//здесь пока только наброски функций

int ft_echo(char *cmd, char **args, char **envp)
{
	int i;

	(void)cmd;
	(void)envp;
	i = 1;
	while(args[i] != NULL)
	{
		printf("%s", args[i]); // просто выводим строку
		i++;
	}
	return (0);
}

int ft_cd(char *cmd, char **args, char **envp)
{
	(void)cmd;
	(void)envp;
	if (args[1] == NULL)
		fprintf(stderr, "minishell: ожидается аргумент для \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("minishell");
	}
	return (0);
}

int		ft_pwd(char *cmd, char **args, char **envp)
{
	(void)args;
	(void)cmd;
	(void)envp;
	printf("ft_pwd\n");
	return(0);
}
int		ft_export(char *cmd, char **args, char **envp)
{
	(void)args;
	(void)cmd;
	(void)envp;
	printf("ft_export\n");
	return(0);
}
int		ft_unset(char *cmd, char **args, char **envp)
{
	(void)args;
	(void)cmd;
	(void)envp;
	printf("ft_unset\n");
	return(0);
}
int		ft_env(char *cmd, char **args, char **envp)
{
	(void)args;
	(void)cmd;
	(void)envp;
	printf("ft_env\n");
	return(0);
}

int ft_exit(char *cmd, char **args, char **envp)
{
	(void)args;
	(void)cmd;
	(void)envp;
	printf("exit\n");
	return (0);
}