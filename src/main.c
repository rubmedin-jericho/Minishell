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

// ----------------- Free AST -----------------
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

void	init_base(char **envp, t_shell *base)
{
	base->envp = envp_dup(envp);
	base->exit_status = 0;
}

char	*make_prompt(void)
{
	char	*str_ret;

	str_ret = COLOR_GOLD "[🐚" COLOR_MAGENTA "MiniConcha$🐚:";
	str_ret = ft_strjoin(str_ret, ">$" COLOR_GOLD"]"COLOR_RESET);
	return (str_ret);
}

void	init_envp(t_shell **shell, char **envp)
{
	int	lenght_e;
	int	i;

	i = 0;
	lenght_e = 0;
	while (envp[lenght_e])
		lenght_e++;
	(*shell)->envp = malloc(sizeof(char *) * (lenght_e + 1));
	if (!(*shell)->envp)
		exit(1);
	while (envp[i])
	{
		(*shell)->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	init_shell(t_shell *sh, char **envp)
{
	init_flags(&sh->flags);
	sh->ast = malloc(sizeof(t_ast));
	if (!sh->ast)
		exit(1);
	sh->exit_status = 0;
	sh->in_pipeline = 0;
	sh->tokens = NULL;
	init_base(envp, sh);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_shell	*shell;
	char	*prompt;

	if (ac > 1 && av[1])
		return (0);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(1);
	printf(MINISHELL_BANNER);
	init_shell(shell, envp);
	while (1)
	{
		prompt = make_prompt();
		str = readline(prompt);
		free(prompt);
		add_history(str);
		if (lexer(&shell->tokens, str, &shell->flags) == -1)
			break ;
		if (parser(shell->tokens, shell->ast) == -1)
		{
			free_tokens(shell);
			break ;
		}
		execute_ast(shell);
		free(str);
	}
	free_env(shell->envp);
	free(shell);
	rl_clear_history();
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
