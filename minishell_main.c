/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:25:43 by rubmedin          #+#    #+#             */
/*   Updated: 2025/10/07 19:36:20 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_command(char *str) /*FUNCION DE PRUEBA - para poner las funciones*/
{
	if(ft_strcmp(str, "pwd") == 0)
		ft_pwd();

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

static void	init_base(char **ae,t_base *base)
{
	base->envp = envp_dup(ae);
	base->exit_status = 0;
}

int	main(int ac, char **av, char **ae)
{
	char *str;
	t_token *tokens;
	int contador;
	t_base	base;

	(void)ac;
	(void)av;
	printf(MINISHELL_BANNER);
	contador = 0;
	init_base(ae, &base);
	while(1)
	{
		tokens = NULL;
		str = readline(COLOR_GOLD "[🐚" COLOR_MAGENTA "MiniConcha$" COLOR_GOLD "🐚>]" COLOR_RESET);
		if (ft_getout(str, &contador))
			break;
		if (lexer(&tokens, str, ae))
			break;
		if(ft_command(str))
			break;
		free(str);
		free(tokens);
	}
	free2d(base.envp);
	rl_clear_history();//Borra historial completo y libera la memoria
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
