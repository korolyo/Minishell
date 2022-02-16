#include "minishell.h"

//TODO: посмотреть, как работает в боевой версии. Если что, брать из var_list
int		ft_pwd(char **args, t_list ***var_list)
{
	char	dir[MAX_DIRNAME];

	(void)var_list;
	(void)args;
	if (!getcwd(dir, MAX_DIRNAME))
		return (0);
	printf("%s\n", dir);
	return (1);
}

int		ft_export( char **args,  t_list ***var_list)
{
	(void)args;
	(void)var_list;
	printf("ft_export\n");
	return(0);
}
int		ft_unset(char **args,  t_list ***var_list)
{
	(void)args;
	(void)var_list;
	printf("ft_unset\n");
	return(0);
}

//тоже игнорируем любые аргументы
int		ft_env(char **args,  t_list ***var_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	(void)args;
	tmp = **var_list;
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (tmp_ptr->is_exported == 1)
			printf("%s=%s\n", tmp_ptr->name, tmp_ptr->value);
		tmp = next;
	}
	return (1);
}

//bash: exit: sdss: numeric argument required
//думаю, что при наличии каких-то еще аргументов, надо просто их игнорировать
int ft_exit(char **args,  t_list ***var_list)
{
	int lvl;
	(void)args;
	printf("exit\n");

	lvl = ft_change_lvl(*var_list, 0);
	if (lvl == 0)
		return (0);
	if (lvl == 2)
	{
		ft_clear_vars(*var_list); //TODO: здесь очистить все
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}