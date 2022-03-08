/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclassie <kclassie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:22 by acollin           #+#    #+#             */
/*   Updated: 2022/03/07 21:04:14 by kclassie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	(ft_del_var)(void *var)
{
	t_var	*tmp_var;

	tmp_var = (t_var *)(var);
	free(tmp_var->value);
	free(tmp_var->name);
	free(tmp_var);
	tmp_var = NULL;
}

int	ft_del_elem(t_list *list, t_list **head, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *head;
	if (list == *head)
	{
		tmp = (*head)->next;
		del((*head)->content);
		free(*head);
		*head = tmp;
		return (1);
	}
	while (tmp->next != list)
		tmp = tmp->next;
	tmp->next = list->next;
	del(list->content);
	free(list);
	return (1);
}

int	ft_unset(char **args, t_list **var_list)
{
	t_list	*tmp_list;
	int		index;

	index = 1;
	while (args[index] != NULL)
	{
		tmp_list = ft_find_var(var_list, args[index]);
		if (tmp_list == NULL)
			ft_check_var(args[index], "unset");
		else
			ft_del_elem(tmp_list, var_list, ft_del_var);
		index++;
	}
	g_exit_status = 0;
	return (0);
}
