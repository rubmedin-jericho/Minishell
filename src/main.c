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

/*
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
		//ft_command(str, base, tokens);
		free(str);
	}
	return (0);
}
*/
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

int main(int argc, char **argv, char **envp) {
    t_shell sh = {0};
    (void)argc;
    (void)argv;
    sh.envp = envp;
    sh.in_pipeline = 0;
    sh.exit_status = 0;

    char *line = readline("MiniShell> ");

	while (line) {
    	if (*line)
     	{
	        t_ast *ast = parse_pipeline(line);
	        sh.ast = ast;
	        execute_ast(&sh);
			free_ast(ast);
      	}
     	free(line);
        line = readline("MiniShell> ");
    }
    free(line);
    clear_history();
    return sh.exit_status;
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
