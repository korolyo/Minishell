#include "minishell.h"

char	*ft_prev_dir(char *pwd_path)
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

int	ft_change_pwd(t_list ***var_list, char *new_path)
{
	t_list	*tmp_list;
	t_var	*tmp_var;

	tmp_list = ft_find_var(var_list, "PWD");
	tmp_var = (t_var *)tmp_list->content;
	if (ft_chng_var(*var_list, "OLDPWD", tmp_var->value, 1) == 0)
		return (0);
	if (ft_chng_var(*var_list, "PWD", new_path, 1) == 0)
		return (0);
	return (1);
}

int	ft_cd_prev_dir(t_list ***var_list)
{
	char	*prev_dir;
	int		i;
	t_list	*tmp_list;
	t_var	*tmp_var;

	tmp_list = ft_find_var(var_list, "PWD");
	tmp_var = (t_var *)tmp_list->content;
	prev_dir = ft_prev_dir(tmp_var->value);
	if (!prev_dir)
		return (0);
	if (chdir(prev_dir) != 0)
	{
		free(prev_dir);
		return (0);
	}
	i = ft_change_pwd(var_list, prev_dir);
	free(prev_dir);
	return (i);
}

int	ft_cd(char **args, t_list ***var_list)
{
	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			return (0);
		return (ft_change_pwd(var_list, getenv("HOME")));
	}
	if (!(ft_strncmp(args[1], ".", 2)))
		return (1);
	if (!(ft_strncmp(args[1], "..", 3)))
		return (ft_cd_prev_dir(var_list));
	else
	{
		if (chdir(args[1]) != 0)
		{
			printf("minishell: cd: %s: %s\n", args[1], strerror(ENOENT));
			return (1);
		}
		return (ft_change_pwd(var_list));
	}
}
