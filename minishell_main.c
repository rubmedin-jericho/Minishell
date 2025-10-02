/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:25:43 by rubmedin          #+#    #+#             */
/*   Updated: 2025/09/29 19:52:48 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_command(char *str) /*FUNCION DE PRUEBA - para poner las funciones*/
{
	char *pwd;

	if(ft_strcmp(str, "pwd") == 0)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
	else if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

static int	 ft_getout(char *str, int *contador)
{
	if (!str)
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

static char **one_split(char *str)
{
	int iter;

	iter = 0;
	count_word = mini_count_word(str)
	while(iter++ < count_word)
	{
		while()
	}
}

int	main(void)
{
	char *str;
	t_token **tokens;
	int contador;
	int count_word;

	printf(MINISHELL_BANNER);
	if(!token)
		return (1);
	contador = 0;
	while(1)
	{
		str = readline("minishell> ");
		tokens = one_split(str);
		if (ft_getout(str, &contador))
			break;
		if (lexer(token, str))
			break;
		if(ft_command(str))
			break;
		//printf("%s\n", str);
		free(str);
	}
	rl_clear_history();//Borra historial completo y libera la memoria
	if(token)
		free(token);
	return (0);
}

/*		readline()
 *	-------------------
 *	La funcion readline(const char *str) es la que te lee el stdin(salida estandar del input) y te lo guarda en str.
 *	Uso readline porque la otra opcion seria read y usar read seria poner mas trabajo porque read tiene 
 *	la limitacion de leer y readline tine ya incorporado como un historial de comandos y 
 *	no necesita buffer size si no que pilla todo el comando.
 *
 *		add_history()
 *	-------------------
 *	El add_history sirve para el tema de agregar un mini historial de comandos.
 *
 * */
