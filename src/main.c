/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:25:43 by rubmedin          #+#    #+#             */
/*   Updated: 2026/01/09 17:04:45 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>


void	init_base(char **envp, t_shell *base)
{
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

char	*print_prompt(t_shell **shell)
{
	char *prompt;
	char *str;

	prompt = make_prompt(shell);
	str = readline(prompt);
	add_history(str);
	free(prompt);
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	char *str;
	t_shell	*shell;
	long	count;

	if (ac > 1 && av[1])
		return (0);
	printf(MINISHELL_BANNER);
  shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	//init_flags(&shell->flags);
	shell->ast = malloc(sizeof(t_ast));
	if (!shell->ast)
		return (1);
	init_base(envp, shell);
	count = 0;
	while(1)
	{
	  init_flags(&shell->flags);
		shell->tokens = NULL;
		str = print_prompt(&shell);
	//	if(count == 0)
	//		write(1, "\n", 1);
		count++;
		if (lexer(&shell->tokens, str, &shell->flags, envp) == -1)
			break ;
		if (parser(shell->tokens, shell->ast) == -1)
			break ;
		if (ft_strncmp(shell->tokens->data, "cd", 2) == 0)
		{
			ft_cd("/home", &shell);
			//	**** This 2 lines is for test the cd, cd go to the /home/ and after withc ls print the directory.
			//	char *args[] = {NULL};
			//	execve("/bin/ls", args, envp);
		}
		if (ft_strncmp(shell->tokens->data, "pwd", 3) == 0)
			ft_pwd(shell);
		free(str);
    //Falta crear funcion  reset flags;
    shell->flags.flag_simple_quot = 0;
    shell->flags.flag_double_quot = 0;
    shell->flags.flag_heredoc = 0;
	}
	free(shell);
	return (0);
}

t_ast *new_cmd_node(char **args) {
    t_ast *node = malloc(sizeof(t_ast));
    node->type = CMD;
    node->args = args;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_ast *new_pipe_node(t_ast *left, t_ast *right) {
    t_ast *node = malloc(sizeof(t_ast));
    node->type = PIPE;
    node->left = left;
    node->right = right;
    node->args = NULL;
    return node;
}

// ----------------- Simple parser -----------------
// Split command line into arguments
char **split_args(char *cmd) {
    int bufsize = 64;
    int i = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token = strtok(cmd, " \t\n");
    while (token) {
        tokens[i++] = strdup(token);
        if (i >= bufsize) {
            bufsize *= 2;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;
    return tokens;
}

// Parse a simple pipeline: cmd1 | cmd2 | cmd3
t_ast *parse_pipeline(char *line) {
    char *saveptr = NULL;
    char *part = strtok_r(line, "|", &saveptr);
    t_ast *root = NULL;

    while (part) {
        char *cmd = strdup(part);
        char **args = split_args(cmd);
        free(cmd);

        t_ast *node = new_cmd_node(args);
        if (!root) {
            root = node; // first command
        } else {
            root = new_pipe_node(root, node); // attach new cmd to the **right**
        }

        part = strtok_r(NULL, "|", &saveptr);
    }
    return root;
}

// ----------------- Free AST -----------------

void free_env(char **env)
{
    int i = 0;

    if (!env)
        return;

    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}
// ----------------- Main -----------------
/*
int main(int argc, char **argv, char **envp) {
    t_shell sh = {0};
    (void)argc;
    (void)argv;
    sh.envp = envp;
    sh.in_pipeline = 0;
    sh.exit_status = 0;

    char *line = readline("MiniShell> ");

	while (line) {
        t_ast *ast = parse_pipeline(line);
        sh.ast = ast;
        execute_ast(&sh);
		free_ast(ast);

     	free(line);
        line = readline("MiniShell> ");
    }
    free(line);
    clear_history();
    return sh.exit_status;
}
*/
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
