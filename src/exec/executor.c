/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:19:54 by jmarques          #+#    #+#             */
/*   Updated: 2025/12/02 10:34:06 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * execute a simple command
 */
void	execute_simple(t_ast *node, t_shell *sh)
{
	char	*path;

	if (!node->args || !node->args[0])
		return ;
	if (is_builtin(node->args[0]))
	{
		builtin(node, sh, node->args[0]);
		if (sh->in_pipeline)
			exit(sh->exit_status);
		return ;
	}
	path = get_path(node->args[0], sh->envp);
	if (!path)
	{
		printf("%s: command not found\n", node->args[0]);
		exit(127);
	}
	execve(path, node->args, sh->envp);
	free(path);
	perror(node->args[0]);
	exit(1);
	
}

void	exec_node_no_fork(t_ast *node, t_shell *sh)
{
	if (node->type == T_PIPE)
		execute_pipe(node, sh);
	else if (node->type == T_STRING)
		execute_simple(node, sh);
	else if (node->type == T_REDIR_IN
		|| node->type == T_REDIR_OUT
		|| node->type == T_REDIR_APPEND)
		execute_redirection(node, sh);
	exit(sh->exit_status);
}

void	exec_node(t_ast *node, t_shell *sh)
{
	pid_t	pid;
	int		status;

	if (sh->in_pipeline)
	{
		exec_node_no_fork(node, sh);
		exit(sh->exit_status);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		sh->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		exec_node_no_fork(node, sh);
		exit(sh->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
}

void	free_tokens(t_shell *sh)
{
	t_token	*tmp;

	while (sh->tokens)
	{
		tmp = sh->tokens->next;
		free(sh->tokens->data);
		free(sh->tokens);
		sh->tokens = tmp;
	}
	sh->tokens = NULL;
}

void	execute_ast(t_ast *ast, t_shell *sh)
{
	if (!sh || !ast)
		return ;
	
	if (ast->type == T_STRING && is_builtin(ast->args[0]) 
		&& !sh->in_pipeline)
    {
        builtin(ast, sh, ast->args[0]);
        return ;
    }
	exec_node(ast, sh);
}
