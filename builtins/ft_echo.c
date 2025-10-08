/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:21:58 by mregada-          #+#    #+#             */
/*   Updated: 2025/10/08 18:22:00 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
/*Modifico echo para que reciba todo como argumentos,
se anade control de -nnn y -n -n
*/
static void	printContent(char **args, int i)
{
	while (args[i + 1])
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("%s", args[i]);
}

static int	n_flag(char *args)
{
	int	i;
	
	i = 0;
	if (!args || args[i] != '-')
		return (0);
	i++;
	while (args[i])
	{
		if(args[i] != 'n')
			return (0);
		i++;
	}
	return(1);
}

int	ft_echo(char **args)
{
	int	i;
	int	line;

	i = 0;
	line = 1;
	if (!args)
	{
		printf("\n");
		return (0);
		
	}
	while (n_flag(args[i]) && args[i])
	{
		line = 0;
		i++;
	}
	printContent(args, i);
	if (line)
		printf("\n");
	return (0);
}
/*
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
		
		if (ft_strcmp(splited[0],"echo") == 0)
		{
			splited++;
			ft_echo(splitted);
			free2d(splited);
		}
		free(splited);
	}
	rl_clear_history();//Borra historial completo y libera la memoria
	return (0);
}
*/
