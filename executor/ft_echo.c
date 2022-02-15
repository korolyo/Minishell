#include "minishell.h"

int ft_echo(char **args, t_list ***var_list) // TODO больше 25 строк
{
	int flag;
	int index;
	int len;

	(void)var_list;
	flag = 1;
	index = 1;
	len = 0;
	while (args[index++] != NULL)
		len++;
	index = 1;
	if (args[index] != NULL)
		flag = ft_strncmp(args[index], "-n", 2);
	if (flag == 0)
	{
		index++;
		len--;
	}
	while (args[index] != NULL)
	{
		printf("%s", args[index]);
		if (len > 1)
			printf(" ");
		len--;
		index++;
	}
	if (flag != 0)
		printf("\n");
	return (1); //успешное завершение
}
