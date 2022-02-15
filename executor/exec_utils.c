#include "minishell.h"

//if id == 0: SHLVL--; if id == 1: SHLVL++
int ft_change_lvl(t_list **var_list, int id)
{
	int 	lvl;
	char	*new_value;
	t_list	*tmp_list;
	t_var	*tmp_var;

	tmp_list = ft_find_var(var_list, "SHLVL");
	tmp_var = (t_var *)tmp_list->content;
	lvl = ft_atoi(tmp_var->value);
	if (id == 0)
		new_value = ft_itoa(lvl - 1);
	if (id == 1)
		new_value = ft_itoa(lvl + 1);
	if (ft_chng_var(var_list, "SHLVL", new_value, 1) == 0)
		return (0);
	free(new_value);
	return (lvl);
}

void	ft_unset_one(t_list *lst)
{
	t_list	*tmp;
	t_var	*tmp_var;

	tmp = lst;
	lst = lst->next;
	tmp_var = (t_var *)(tmp->content);
	if (tmp_var)
	{
		free(tmp_var->value);
		free(tmp_var->name);
		free(tmp_var);
	}
	free(tmp);
}
