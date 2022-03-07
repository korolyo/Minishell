/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:16:37 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:16:39 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var(char *var, char *check_cmd)
{
	int	i;

	i = 0;
	if ((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z')
		|| (var[i] == '_' && var[i + 1] != '\0'))
	{
		while (ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_'
			|| var[i] == '$' || var[i] == '\\' || var[i] == '%' || var[i] == '/')
			i++;
	}
	if (var[i] != '\0')
	{
		printf("minishell: %s: '%s': not a valid identifier\n", check_cmd, var);
		return (0);
	}
	return (1);
}

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
