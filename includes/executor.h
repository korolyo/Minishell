/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/06 20:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft.h"
# include <dirent.h>
# include <stdlib.h>

// Executor:
# define MAX_FILENAME 	255

//Executor:
typedef struct s_cmd
{
	char		*cmd;
	int			(*f_cmd)(char **args, t_list **var_list);
}				t_cmd;

typedef struct s_vlist
{
	struct s_var	*content;
	struct s_vlist	*next;
}					t_vlist;

//0 - переменная среды, 1 - переменная окружения
typedef struct s_var
{
	char		*name;
	char		*value;
	int			is_exported;
}				t_var;

typedef struct s_misc
{
	int			i;
	int			num_of_pipes;
	int			cmd_count;
	int			*fdpipe;
}				t_misc;

//builtings
int		ft_echo(char **args, t_list **var_list);
int		ft_cd(char **args, t_list **var_list);
int		ft_pwd(char **args, t_list **var_list);
int		ft_export(char **args, t_list **var_list);
int		ft_unset(char **args, t_list **var_list);
int		ft_env(char **args, t_list **var_list);
int		ft_exit(char **args, t_list **var_list);

//Execution
int		ft_start(t_tlist *tokens, t_list **var_list);
int		ft_start_execution(t_tlist *tokens, t_list **var_list, t_misc *misc);
int		ft_execution(t_tlist *tokens, t_list **var_list, t_misc *misc);
t_list	*ft_find_var(t_list **var_list, char *var_name);
int		ft_save_var(t_list **var_list, char *var, int var_id);
t_var	*ft_make_var(char *var, t_var *variable);
int		ft_clear_vars(t_list **var_list);
int		ft_chng_var(t_list **var_list, char *var_name,
			char *new_value, int var_id);
int		ft_change_lvl(t_list **var_list, int id);
int		ft_clear_path_list(char ***path_list);
int		ft_add_status(t_list **var_list, int status);
int		ft_cmd_error(char *cmd);
char	**ft_parse_path(t_list **var_list, char *cmd);
char	*ft_find_path(char **path_list, char *executor_name);
int		ft_join_path(char *args, char *tmp_path, char **path_list,
			char **executor_path);
int		ft_execute_cmd(char *path, t_tlist *tokens, t_misc *misc);
int		ft_redirection(t_tlist *tokens, int *tmp_in, int *tmp_out);
void	ft_restore_fd(int tmp_in, int tmp_out);
int		ft_check_if_var(char **args, t_list **var_list, int task_id);
int		ft_check_var(char *args, char *check_cmd);
void	init_misc(t_misc *misc, t_tlist *tokens);
void	print_var_list(t_list **var_list);

#endif
