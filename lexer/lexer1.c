/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// DO THE LOGIC
char	*lexer_quotes(char *prompt, int *i, t_list **var_list)
{
	char	*tmp;
	int 	j;

	j = *i;
	tmp = prompt;
	if (tmp[*i] == '\'')
	{
		while (tmp[(*i)] != '\'')
			(*i)++;
	}
	if (tmp[*i] == '\"')
	{
		while (tmp[(*i)] != '\"' || tmp[(*i)] != '$')
			(*i)++;
		if (prompt[(*i)] == '$')
			tmp = lexer_dollar(prompt, i, var_list);
	}
	free(prompt);
	return (tmp);
}
//TO DO: global var(?) that contain error value
char	*lexer_dollar(const char *prompt, int *i, t_list **var_list)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_list	*tmp4;
	t_var	*tmp5;
	int		j;

	tmp = ft_substr(prompt, 0, (*i));
	(*i)++;
	if (is_key(prompt[*i]) || prompt[*i] == '?')
	{
		j = *i;
		while (is_key(prompt[*i]))
			(*i)++;
		tmp2 = ft_substr(prompt, j, (*i) - j + 1);
		tmp3 = ft_substr(prompt, (*i) + 1, ft_strlen(prompt) - (*i) - 1);
		tmp4 = ft_find_var(var_list, tmp2);
		free(tmp2);
		tmp5 = (t_var *)tmp4->content;
		printf("check1\n");
		tmp2 = ft_strdup(tmp5->value);
		*i = j + ft_strlen(tmp2);
		printf("%d\n", *i);
		tmp = ft_strjoin(tmp, tmp2);
		if (tmp2)
			free(tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		if (tmp3)
			free(tmp3);
		free((char *)prompt);
	}
	if (ft_isdigit(prompt[*i]))
		(*i)++;
	return (tmp);
}

char	*lexer_redir(t_tlist **tokens, char *prompt, int i)
{
	t_tlist	*tmp;
	char	*str;
	int 	j;

	j = i;
	if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		tmp = tlistnew(HERE_DOC);
		i++;
	}
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		tmp = tlistnew(REDIR_APPEND);
		i++;
	}
	else if (prompt[i] == '>')
		tmp = tlistnew(REDIR);
	else if (prompt[i] == '<')
		tmp = tlistnew(REDIR_INPUT);
	i++;
	while (prompt[i] == ' ' || ft_isalpha(prompt[i])
		|| ft_isdigit(prompt[i]))
		i++;
	if (tmp->type == REDIR || tmp->type == REDIR_APPEND ||
		tmp->type == REDIR_INPUT)
		tmp->cmd[1] = ft_substr(prompt, j + 1, i - j);
	str = str_delete_part(prompt, j, i, DELETE_MID);
	tlistadd_back(tokens, tmp);
	return (str);
}

void	lexer_cmd(t_tlist **tokens, char *prompt, int *i)
{
	t_tlist	*tmp;
//	char	*tmp_str;
//	int 	j;
	int		count;

//	j = *i;
	count = -1;
	tmp = tlistnew(CMD);
	while (!ft_strchr("<>|", prompt[(*i)]))
		(*i)++;
//	tmp_str = ft_substr(prompt, )
	if (prompt[*i] == '<' || prompt[*i] == '>')
		lexer_redir(tokens, prompt, *i);
//	printf("prompt = %s\n", prompt);
//	printf("i = %d j = %d\n", *i, j);
//	tmp_str = ft_substr(prompt, j, *i - j);
//	printf("tmp_str = %s\n", tmp_str);
	tmp->cmd = ft_quotes_split(prompt, ' ');
	while (tmp->cmd[++count])
		printf("count = %d tlist->cmd = |%s|\n", count, tmp->cmd[count]);
//	printf("cmd check\n");
	tlistadd_back(tokens, tmp);

}

//void	lexer_env(t_tlist **tokens, char *prompt, int *i)
//{
//	t_tlist *tmp;
//	char	*str;
//	int		j;
//
//	(*i)++;
//	j = *i;
//	tmp = tlistnew(ENV);
//	if (!(ft_isalpha(prompt[*i])) || prompt[*i] != '?')
//		tmp->cmd = NULL;
//	else if (prompt[*i] == '?')
//		(*i)++;
//	else if (ft_isalpha(prompt[*i]))
//	{
//		while (ft_isprint(prompt[*i]) || ft_isdigit(prompt[*i]))
//			(*i)++;
//	}
//	str = ft_substr(prompt, j, *i - j);
//	tlistadd_back(tokens, tmp);
//}

char	*lexer_pipe(t_tlist **tokens, int *i)
{
	t_tlist	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	tmp = tlistnew(PIPE);
	tlistadd_back(tokens, tmp);
	return (str);
}
