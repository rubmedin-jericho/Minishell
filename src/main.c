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
#include <readline/history.h>

int	g_signal = 0;

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

t_shell	init_shell(char **envp)
{
	t_shell	sh;

	init_flags(&sh.flags);
	sh.ast = malloc(sizeof(t_ast));
	if (!sh.ast)
		exit(1);
	sh.exit_status = 0;
	sh.in_pipeline = 0;
	sh.tokens = NULL;
	sh.envp = envp_dup(envp);
	signals_init();
	return (sh);
}

void	free_shell_loop(t_shell *sh)
{
	if (sh->tokens)
		free_tokens(sh);
	sh->tokens = NULL;
	free(sh->str);
}

void	shell_loop(t_shell *sh)
{
	while (1)
	{
		sh->str = readline("minishell> ");
		if (sh->str == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (sh->str[0] == '\0')
		{
			free(sh->str);
			continue ;
		}
		add_history(sh->str);
		lexer(sh);
		parser(sh);
		execute_ast(sh);
		free_shell_loop(sh);
		g_signal = 0;
	}
}

/*int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac > 1 && av[1])
		return (0);
	shell = init_shell(envp);
	shell_loop(&shell);
	free_shell_loop(&shell);
	free_env(shell.envp);
	rl_clear_history();
	return (g_signal);
}
*/
int	main(int ac, char **av)
{
	char *str;
	t_flags *flags;

	flags = NULL;
	(void)ac;

	str = cut_str(av[1], (char)av[2], flags);
	printf("[str]:[%s]\n", str);
	return (0);
}
/*		readline()
 *	-------------------
 *	La funcion readline(const char *str) es la que te lee
 *  el stdin(salida estandar del input) y te lo guarda en str.
 *	Uso readline porque la otra opcion seria read y usar
 *  read seria poner mas trabajo porque read tiene
 *	la limitacion de leer y readline tine ya incorporado
 *  como un historial de comandos y
 *	no necesita buffer size si no que pilla todo el comando.
 *
 *		add_history()
 *	-------------------
 *	El add_history sirve para el tema de agregar un mini
 *  historial de comandos.
 *
 * */
