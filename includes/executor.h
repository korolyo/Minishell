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

# define MAX_FILENAME 	255

typedef struct s_cmd
{
	char		*cmd;
	int			(*f_cmd)(char **args, t_list **var_list);
}				t_cmd;

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
void	ft_print_export(char **sorted_env, t_list **var_list, int len);

//Execution
int		ft_start(t_tlist *tokens, t_list **var_list);
int		ft_start_execution(t_tlist *tokens, t_list **var_list, t_misc *misc);
int		ft_execution(t_tlist *tokens, t_list **var_list, t_misc *misc);
int		ft_execute_cmd(char *path, t_tlist *tokens, t_misc *misc);
int		ft_redirection(t_tlist *tokens, int *tmp_in, int *tmp_out);
void	ft_restore_fd(int tmp_in, int tmp_out);
void	init_misc(t_misc *misc, t_tlist *tokens);

//Var handling
t_list	*ft_find_var(t_list **var_list, char *var_name);
int		ft_save_var(t_list **var_list, char *var, int var_id);
void	ft_make_var(char *var, char **var_name, char **var_value);
int		ft_clear_vars(t_list *var_list);
int		ft_chng_var(t_list **var_list, char *var_name,
			char *new_value, int var_id);
int		ft_check_if_var(char **args, t_list **var_list, int task_id);
int		ft_change_lvl(t_list **var_list, int id);
int		ft_check_var(char *var, char *check_cmd);
int		ft_var_utils(t_list **var_list, char *var_name, char *new_value,
			int var_id);
t_list	*save_var(void);
int		ft_make_list(t_list **var_list, char *var_name, char *var_value,
			int var_id);
int		ft_add_status(t_list **var_list);
int		ft_wait_pid(pid_t pid);

//Utils
int		ft_clear_arr(char **arr);
int		ft_cmd_error(char *cmd);
char	**ft_parse_path(t_list **var_list, char *cmd);
char	*ft_find_path(char **path_list, char *executor_name);
int		ft_join_path(char *args, char *tmp_path, char **path_list,
			char **executor_path);
int		ft_clear_execution(char **path_list, char *tmp_path,
			char *executor_path);

#endif
