#include "../minishell.h"
#include <stdio.h>

int	ft_echo(char *content, int n)
{
	if (content == NULL)
	{
		if (n == 1)
			return (0);
		printf("\n");
	}
	else
	{
		if (n == 1)
		{
			printf("%s", content);
			return (0);
		}
		printf("%s\n", content);
	}
	return (0);
}
/*
Este echo de momento recibe el flag -n como int, 
en funcion de como se reciban los flags se cambia
dejo prueba con main debajo: 
static int	 ft_getout(char *str, int *contador)
{
	if (!str)
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (str)
		add_history(str);
	if (*contador == 3)
	{
		*contador = 0;
		rl_clear_history();
		add_history(str);
	}
	*contador += 1;
	return (0);
}

int	main(void)
{
	char *str;
	char **splited;
	int contador;

	printf(MINISHELL_BANNER);
	contador = 0;
	while(1)
	{
		str = readline("minishell> ");
		splited = ft_split(str, ' ');
		if (ft_getout(splited[0], &contador))
			break;
		//ft_command(splited[0]);
		//printf("%s\n", str);
		
		if (ft_strcmp(splited[0],"echo") == 0)
		{
			int n = 0;
			if (ft_strcmp(splited[1],"-n") == 0)
			{
				n = 1;
				ft_echo(splited[2],n);
			}
			else
				ft_echo(splited[1],n);
			free2d(splited);
		}
		free(splited);
	}
	rl_clear_history();//Borra historial completo y libera la memoria
	return (0);
}
*/