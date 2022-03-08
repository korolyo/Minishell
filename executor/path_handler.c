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

char	*ft_find_path(char **path_list, char *executor_name)
{
	DIR				*dir;
	struct dirent	*ent;
	int				index;

	index = -1;
	while (path_list[++index] != NULL)
	{
		dir = opendir(path_list[index]);
		if (dir != NULL)
		{
			ent = readdir(dir);
			while (ent != NULL)
			{
				if (!ft_strncmp(ent->d_name, executor_name, MAX_FILENAME))
				{
					closedir(dir);
					return (path_list[index]);
				}
				ent = readdir(dir);
			}
		}
		closedir(dir);
	}
	return (NULL);
}

char	**ft_parse_path(t_list **var_list, char *cmd)
{
	const char	*path;
	char		**path_list;
	t_list		*tmp_list;
	t_var		*tmp_var;

	tmp_list = ft_find_var(var_list, "PATH");
	if (!tmp_list)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		return (NULL);
	}
	tmp_var = (t_var *)tmp_list->content;
	path = tmp_var->value;
	path_list = ft_split(path, ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

int	ft_join_path(char *args, char *tmp_path, char **path_list, char **exec_path)
{
	tmp_path = ft_strjoin("/", &args[0]);
	if (!tmp_path)
	{
		ft_clear_arr(path_list);
		return (0);
	}
	*exec_path = ft_strjoin(ft_find_path(path_list, args), tmp_path);
	if (!*exec_path)
	{
		free(path_list);
		free(tmp_path);
		return (0);
	}
	free(tmp_path);
	return (1);
}
