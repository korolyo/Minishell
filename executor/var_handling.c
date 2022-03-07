/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:55 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:57 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_find_var(t_list **var_list, char *var_name)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	tmp = *var_list;
	if (!var_name)
		return (NULL);
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (!(ft_strncmp(var_name, tmp_ptr->name, MAX_FILENAME)))
			return (tmp);
		tmp = next;
	}
	return (NULL);
}

int	ft_chng_var(t_list **var_list, char *var_name, char *new_value, int var_id)
{
	t_list	*tmp_list;
	t_var	*tmp_val;

	tmp_list = ft_find_var(var_list, var_name);
	if (tmp_list == NULL)
		return (ft_save_var(var_list, ft_strjoin(ft_strjoin(var_name,
						"="), new_value), var_id));
	tmp_val = (t_var *)tmp_list->content;
	if (!new_value)
	{
		tmp_val->is_exported = var_id;
		return (1);
	}
	tmp_val->value = malloc(sizeof(char) * (ft_strlen(new_value) + 1));
	if (!tmp_val->value)
		return (0);
	strlcpy(tmp_val->value, new_value, ft_strlen(new_value) + 1);
	tmp_val->is_exported = var_id;
	return (1);
}

int	ft_clear_vars(t_list **var_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_var;

	tmp = *var_list;
	while (tmp)
	{
		next = tmp->next;
		tmp_var = (t_var *)(tmp->content);
		if (tmp_var)
		{
			free(tmp_var->value);
			free(tmp_var->name);
			free(tmp_var);
			tmp_var = NULL;
		}
		free(tmp);
		tmp = next;
	}
	var_list = NULL;
	return (0);
}

t_var	*ft_make_var(char *var, t_var *variable, t_list **var_list, int id)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	while (var[len1] != '=' && var[len1] != '\0')
		len1++;
	variable->name = malloc(sizeof(char) * (len1 + 1));
	if (!variable->name)
		return (NULL);
	ft_strlcpy(variable->name, var, len1 + 1);
	while (var[len1++] != '\0')
		len2++;
	if (len2 > 0)
	{
		variable->value = malloc(sizeof(char) * (len2 + 1));
		if (!variable->value)
			free(variable->name);
		ft_strlcpy(variable->value, &var[len1 - len2], len2 + 1);
	}
	else
		variable->value = NULL;
	if (ft_find_var(var_list, variable->name))
	{
		ft_chng_var(var_list, variable->name, variable->value, id);
		return (NULL);
	}
	return (variable);
}

//var_id: 0 - isn't exported to env; 1 - is exported to env
int	ft_save_var(t_list **var_list, char *var, int var_id)
{
	t_var	*variable;
	t_list	*new_val;
	void	*tmp_ptr;

	if (!var || !var_list)
		return (0);
	variable = malloc(sizeof(t_var));
	if (!variable)
		return (ft_clear_vars(var_list));
	if (!ft_make_var(var, variable, var_list, var_id))
	{
		if (variable->name)
			free(variable->name);
		if (variable->value)
			free(variable->value);
		free(variable);
	}
//	return (ft_clear_vars(var_list));
	variable->is_exported = var_id;
	tmp_ptr = variable;
	new_val = ft_lstnew(tmp_ptr);
	if (!new_val)
		return (ft_clear_vars(var_list));
	ft_lstadd_back(var_list, new_val);
	return (1);
}
