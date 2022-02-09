//временный файл для execution.c

#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>

# define MALLOC_ERR	1
# define FORK_ERR	2

typedef struct	s_cmd
{
	char	*cmd;
	int		(*f_cmd)(char *cmd, char **args, char **envp);
}				t_cmd;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		start_executing(char *cmd, char **args, char **envp);
int		ft_execution(char *cmd, char **argv, char **envp);

//builtings
int		ft_echo(char *cmd, char **argv, char **envp);
int		ft_cd(char *cmd, char **argv, char **envp);
int		ft_pwd(char *cmd, char **argv, char **envp);
int		ft_export(char *cmd, char **argv, char **envp);
int		ft_unset(char *cmd, char **argv, char **envp);
int		ft_env(char *cmd, char **argv, char **envp);
int		ft_exit(char *cmd, char **argv, char **envp);

#endif
