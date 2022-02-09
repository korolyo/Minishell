

#include "minishell.h"

//char **ft_do_args(char *cmd, char **args)
//{
//
//}

int start_executing(char *cmd, char **args, char **envp)

{
	int				index;
	//char 			**args_dup;
	extern char		**environ;
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
		if (cmd == builtins[index].cmd)
			return (builtins[index].f_cmd(cmd, args, envp));
	}
	if (index == 7)
	{
		//args_dup = ft_do_args(cmd, args); собирает из args нужный для execve формат
		ft_execution(cmd, args, envp);
	}
	return (0);
}
