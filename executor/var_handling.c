/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:55 by acollin           #+#    #+#             */
/*   Updated: 2022/03/07 19:35:40 by kclassie         ###   ########.fr       */
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
		return (ft_var_utils(var_list, var_name, new_value, var_id));
	tmp_val = (t_var *)tmp_list->content;
	if (!new_value)
	{
		tmp_val->is_exported = var_id;
		return (1);
	}
	if (tmp_val->value)
		free(tmp_val->value);
	tmp_val->value = malloc(sizeof(char) * (ft_strlen(new_value) + 1));
	if (!tmp_val->value)
		return (0);
	ft_strlcpy(tmp_val->value, new_value, ft_strlen(new_value) + 1);
	tmp_val->is_exported = var_id;
	free(new_value);
	return (1);
}

void	ft_make_var(char *var, char **var_name, char **var_value)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	while (var[len1] != '=' && var[len1] != '\0')
		len1++;
	*var_name = malloc(sizeof(char) * (len1 + 1));
	ft_strlcpy(*var_name, var, len1 + 1);
	while (var[len1++] != '\0')
		len2++;
	*var_value = malloc(sizeof(char) * (len2 + 1));
	if (len2 > 0)
		ft_strlcpy(*var_value, &var[len1 - len2], len2 + 1);
	else
		*var_value = NULL;
}

int	ft_make_list(t_list **var_list, char *var_name, char *var_value, int var_id)
{
	t_var	*variable;
	t_list	*new_val;
	void	*tmp_ptr;

	variable = malloc(sizeof(t_var));
	if (!variable)
		return (ft_clear_vars(*var_list));
	variable->name = ft_strdup(var_name);
	variable->value = ft_strdup(var_value);
	variable->is_exported = var_id;
	free(var_name);
	free(var_value);
	tmp_ptr = variable;
	new_val = ft_lstnew(tmp_ptr);
	if (!new_val)
		return (ft_clear_vars(*var_list));
	ft_lstadd_back(var_list, new_val);
	return (1);
}

int	ft_save_var(t_list **var_list, char *var, int var_id)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	var_value = NULL;
	if (ft_isdigit(var[0]))
		return (ft_cmd_error(var));
	ft_make_var(var, &var_name, &var_value);
	if (ft_find_var(var_list, var_name))
	{
		ft_chng_var(var_list, var_name, var_value, 1);
		return (1);
	}
	return (ft_make_list(var_list, var_name, var_value, var_id));
}
