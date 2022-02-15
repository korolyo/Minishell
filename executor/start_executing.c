#include "minishell.h"
//ft_make_env_list
//ft_make_var_list

int ft_start_execution(char **args, t_list **var_list)
{
	int				index;
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
		if (!(strncmp(args[0], builtins[index].cmd, 7)))
			return (builtins[index].f_cmd(args, &var_list));
	}
	if (index == 7)
	{
		return (ft_execution(args, var_list));
	}
	return (1);
}

t_btree *ft_start(t_btree *ast, t_list **var_list)
{
//	int i = -1;
	if (ast)
	{
//		printf("check\n");
		ft_start(ast->left, var_list);
		if (ast->type == CMD)
		{
//			printf("CMD = [%s]\n", ast->value[0]);
//			while (ast->value[++i])
//				printf("cmd = [%s]\n", ast->value[i]);
			ft_start_execution(ast->value, var_list);
		}
		ft_start(ast->right, var_list);
		return (ast);
	}
	return (NULL); //успешное завершение
}

