#include "minishell.h"
//ft_make_env_list
//ft_make_var_list

int start_executing(char **args)

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
	return (1); //успешное завершение
}
