#include "minishell.h"
//ft_make_env_list
//ft_make_var_list

int start_execution(char **args)
{
	int				index;
	//extern char		**environ;
	static t_cmd	builtins[] = {
			{"echo", ft_echo},
			{"cd", ft_cd},
			{"pwd", ft_pwd},
			{"export", ft_export},
			{"unset", ft_unset},
			{"env", ft_env},
			{"exit", ft_exit}
	};

	index = -1;
	while (++index < 7)
	{
		if (args[0] == builtins[index].cmd)
			return (builtins[index].f_cmd(args));
	}
	if (index == 7)
	{
		//проверять, если это переменная
		return (ft_execution(args));
	}
	return (1);
}

t_btree *start(t_btree *ast)
{
//	int i = -1;
	if (ast)
	{
//		printf("check\n");
		start(ast->left);
		if (ast->type == CMD)
		{
//			printf("CMD = [%s]\n", ast->value[0]);
//			while (ast->value[++i])
//				printf("cmd = [%s]\n", ast->value[i]);
			start_execution(ast->value);
		}
		start(ast->right);
		return (ast);
	}
	return (NULL); //успешное завершение
}

