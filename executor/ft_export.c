/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:18 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:20 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_insert_srt (t_list *sort_list, t_list *item)
{
	t_var	*tmp_var;
	t_var	*tmp_var2;
	t_list	*tmp_list;

	if (sort_list)
		tmp_var = (t_var *)sort_list->content;
	else
		tmp_var = NULL;
	tmp_var2 = (t_var *)item->content;
	if (!sort_list || ft_strncmp(tmp_var2->name, tmp_var->name, 250) < 0)
	{
		item->next = sort_list;
		sort_list = item;
	}
	else
	{
		tmp_list = sort_list;
		while (tmp_list)
		{
			if (tmp_list->next == NULL || ft_strncmp(tmp_var2->name, tmp_var->name, 250) < 0)
			{
				item->next = tmp_list->next;
				tmp_list->next = item;
				break;
			}
			tmp_list = tmp_list->next;
		}
	}
	return (sort_list);
}

t_list *ft_sort_list(t_list **var_list)
{
	t_list *sort_list;
	t_list *tmp_list;
	t_list *tmp_list2;

	tmp_list = *var_list;
	while(tmp_list)
	{
		tmp_list2 = tmp_list;
		tmp_list = tmp_list->next;
		sort_list = ft_insert_srt(sort_list, tmp_list2);
	}
	return (sort_list);
}

int ft_print_export(t_list **sort_list)
{
	t_list	*tmp;
	t_list	*next;
	t_var	*tmp_ptr;

	tmp = *sort_list;
	while (tmp)
	{
		next = tmp->next;
		tmp_ptr = (t_var *)tmp->content;
		if (tmp_ptr->is_exported == 1 && *tmp_ptr->name != '_')
			printf("declare -x %s=\"%s\"\n", tmp_ptr->name, tmp_ptr->value);
		tmp = next;
	}
	ft_clear_vars(sort_list);
	return (1);
}

int		ft_export(char **args,  t_list **var_list)
{
	t_list	*sort_list;
	t_list	*tmp_list;
//	int 	index;
//
//	index = 1;
//	while (args[index] != NULL)
//	{
////		tmp_list = ft_find_var(var_list, args[index]);
////		if (tmp_list == NULL && ft_strchr(args[index], '=') == NULL)
////		{
////			ft_check_var(args[index], "export");
////			return (1);
////		}
//		ft_save_var(var_list, args[index], 1);
//		index++;
//	}
	tmp_list = *var_list;
	if (args[1] == NULL)
	{
		sort_list = ft_sort_list(&tmp_list);
		return (ft_print_export(&sort_list));
	}
	return(1);
}
