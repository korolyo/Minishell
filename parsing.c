/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*ft_dollar(char *prompt, int *i, t_data *data, char **envp)
{
	int		j;
	int		k;
	int		z;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = *i;
	k = -1;
	z = 0;

	while (prompt[++(*i)])
		if (!is_key(prompt[*i]))
			break ;
	if (*i == j + 1)
		return(prompt);
	data->env_key = ft_substr(prompt, j + 1, *i - j);
	temp3 = ft_substr(prompt, *i + 1, ft_strlen(prompt) - *i -1);
	while (envp[++k])
	{
		if ((strstr(envp[k], data->env_key)))
		{
			while (envp[k][z] != '=' && envp[k][z])
				z++;
			temp2 = ft_substr(envp[k], 0, z);
			if (ft_strncmp(data->env_key, temp2, ft_strlen(temp2)) == 0)
				break ;
		}

	}
	temp2 = ft_substr(envp[k], z + 1, ft_strlen(envp[k] - z));
//	printf("temp2 = %s", temp2);
	temp = ft_substr(prompt, 0, j);
	temp = ft_strjoin(temp, temp2);
	temp = ft_strjoin(temp, temp3);
//	temp = getenv(data->env_key);
//	printf("temp = %s\n", temp);
	free(prompt);
	return (prompt);
}

char	*ft_quotes(char *prompt, int *i)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = *i;
	while (prompt[++(*i)])
		if (prompt[(*i)] == '\'')
			break ;
	temp = ft_substr(prompt, 0, j);
	temp2 = ft_substr(prompt, j + 1, *i - j - 1);
	temp3 = ft_substr(prompt, *i + 1, ft_strlen(prompt) - *i - 1);
	temp = ft_strjoin(temp, temp2);
	temp = ft_strjoin(temp, temp3);
	free(prompt);
	return (temp);
}

char	*ft_backslash(char *prompt, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(prompt, 0, *i);
	tmp2 = ft_strdup(prompt + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(prompt);
	++(*i);
	return (tmp);
}

char	*parse_line(char *prompt, char **envp)
{
//	""  ''  \  $  ;  '_'  |  >  >>  <
	int		i;
	t_data	data;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '\'')
			prompt = ft_quotes(prompt, &i);
		if (prompt[i] == '$')
			prompt = ft_dollar(prompt, &i, &data, envp);
		if (prompt[i] == '\\')
			prompt = ft_backslash(prompt, &i);
		if (prompt[i] == '\"')
			prompt = ft_doublequotes(prompt, &i);
//		if (str[i]) == '\ ')
//			ft_whitespace(str, i);
//		if (str[i] == '\;')
//			ft_semicolon(str, i);
//		if (str[i] == '\|')
//			ft_pipe(str, i);
//		if (str[i] == '>' || str[i] == '>>' || str[i] == '<')
//			ft_redirect(str, i);
	}
//	free(&data);
	return (prompt);
}
