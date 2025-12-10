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


void	init_base(char **envp, t_shell *base, t_token *tokens)
{
	(void)tokens;
	base->envp = envp_dup(envp);
	base->exit_status = 0;
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

int	count_char(char *str, char pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == pattern)
			j++;
		i++;
	}
	return (j);
}

char	*cut_path(char *path, char	*usr_env, char pattern)
{
	char	**split;
	char	**usr;
	int		lenght_max;
	int		lenght_usr;
	char	*str_ret;
	int		i;

	i = 1;
	str_ret = ft_strdup("");
	lenght_max = count_char(path, pattern);
	split = ft_split(path, pattern);
	usr = ft_split(usr_env, '=');
	lenght_usr = ft_strlen(usr[1]);
	if(!split[0] && path[4] == '/')
		str_ret = "/";
	while(split[i] && i <= lenght_max)
	{
		if(ft_strncmp(split[i], usr[1], lenght_usr) == 0 && 
		ft_strncmp(split[i - 1], "home", 4) == 0)
		{
			free(str_ret);
			str_ret = "";
			str_ret = ft_strjoin(str_ret, "~");
		}
		else
		{
			str_ret = ft_strjoin(str_ret, "/");
			str_ret = ft_strjoin(str_ret, split[i]);
			i++;
		}
	}
	return (str_ret);
}

char	*search_envp(char *s, char **envp)
{
	int	i;
	char *path_readline;
	int	lenght_str;

	i = 0;
	lenght_str = ft_strlen(s);
	path_readline = "\0";
	while (envp[i])
	{
		if(ft_strncmp(s, envp[i], lenght_str) == 0)
		{
			path_readline = cut_path(envp[i], envp[43], '/');
			return (path_readline);
		}
		i++;
	}
	return (envp[i]);
}

char	*make_prompt(t_shell **shell)
{
	char	*path_readline;
	char	*str_ret;

	path_readline = search_envp("PWD=", (*shell)->envp);
	str_ret = COLOR_GOLD "[🐚" COLOR_MAGENTA "MiniConcha$🐚:";
	str_ret = ft_strjoin(str_ret, path_readline);
	str_ret = ft_strjoin(str_ret,	">$" COLOR_GOLD"]"COLOR_RESET);
	return (str_ret);
}

int	lenght_envp(char **envp)
{
	int	lenght;

	lenght = 0;
	while(envp[lenght])
		lenght++;
	return (lenght);
}

void init_envp(t_shell **shell, char **envp)
{
	int	lenght_e;
	int	i;

	i = 0;
	lenght_e = lenght_envp(envp);
	(*shell)->envp = malloc(sizeof(char *) * (lenght_e + 1));
	if(!(*shell)->envp)
		return ;
	while(envp[i])
	{
		(*shell)->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char *str;
	t_shell	*shell;
	char *prompt;

	if (ac > 1 && av[1])
		return (0);
	printf(MINISHELL_BANNER);
	shell = malloc(sizeof(t_shell));
	init_envp(&shell, envp);
	if (!shell)
		return (1);
	init_flags(&shell->flags);
	shell->ast = malloc(sizeof(t_ast));
	if (!shell->ast)
		return (1);
	while(1)
	{
		shell->tokens = NULL;
		prompt = make_prompt(&shell);
		str = readline(prompt);
		add_history(str);
		if (lexer(&shell->tokens, str, &shell->flags) == -1)
			break ;
		if (parser(shell->tokens, shell->ast) == -1)
			break ;
		init_base(envp, shell, shell->tokens);
		if (ft_strncmp(shell->tokens->data, "cd", 2) == 0)
		{
			ft_cd("/home", &shell);
			//	**** This 2 lines is for test the cd, cd go to the /home/ and after withc ls print the directory.
			//	char *args[] = {NULL};
			//	execve("/bin/ls", args, envp);
		}
		if (ft_strncmp(shell->tokens->data, "pwd", 3) == 0)
			ft_pwd(shell);
		//ft_command(str, base, tokens);
		free(prompt);
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
 * 
 * */
