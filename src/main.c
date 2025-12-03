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

/*
static int ft_command(char *str, t_base *base, t_token *tokens) FUNCION DE PRUEBA - para poner las funciones
{
	if(ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd();
	if(ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(base);
	if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
	{
		free(tokens);
		ft_exit(base, ft_split(str, ' '), 0);
	}
	return (0);
}
*/
//static int	count_commands(t_token *tokens)
//{
//	int	i;
//
//	i = 0;
//	while(tokens)
//	{
//		if(tokens->type_tok == 4)
//			i++;
//		tokens = tokens->next;
//	}
//	return (i);
//}

//static void	fill_commands(t_base *base, t_token *tokens)
//{
//	int	i;
//	int	lenght_commands;
//	t_token *iter_tmp;
//
//	i = 0;
//	iter_tmp = tokens;
//	lenght_commands = count_commands(tokens);
//	base->commands = malloc(sizeof(char *) * (lenght_commands + 1));
//	if(!base->commands)
//		return ;
//	while (iter_tmp)
//	{
//		if (iter_tmp->type_tok == 4)
//		{
//			base->commands[i] = ft_strdup(iter_tmp->data);
//			i++;
//		}
//		iter_tmp = iter_tmp->next;
//	}
//	base->commands[i] = NULL;
//}

void	init_base(char **envp, t_shell *base, t_token *tokens)
{
	(void)tokens;
	base->envp = envp_dup(envp);
	base->exit_status = 0;
//	fill_commands(base, tokens);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("[%s]\n", envp[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char *str;
	t_shell	*shell;

	if (ac > 1 && av[1])
		return (0);
	printf(MINISHELL_BANNER);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_flags(&shell->flags);
	shell->ast = malloc(sizeof(t_ast));
	if (!shell->ast)
		return (1);
	while(1)
	{
		shell->tokens = NULL;
		str = readline(COLOR_GOLD "[🐚" COLOR_MAGENTA "MiniConcha$" COLOR_GOLD "🐚>]" COLOR_RESET);
		add_history(str);
		if (lexer(&shell->tokens, str, envp, &shell->flags) == -1)
			break ;
		if (parser(shell->tokens, shell->ast) == -1)
			break ;
		init_base(envp, shell, shell->tokens);
		if (ft_strncmp(shell->tokens->data, "cd", 2))
			ft_cd("/home", envp);
		if (ft_strncmp(shell->tokens->data, "pwd", 3))
			ft_pwd(shell);
		//ft_command(str, base, tokens);
		free(shell);
		free(str);
	}
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
