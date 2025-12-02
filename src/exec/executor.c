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

void	execute_simple(t_ast *node, t_shell *sh)
{
	char	*path;

	path = get_path(node->args[0], sh->envp);
	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", node->args[0]);
		exit(127);
	}
	execve(path, node->args, sh->envp);
	perror(node->args[0]);
	exit(1);
}

void	exec_node(t_ast *node, t_shell *sh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (node->type == CMD)
			execute_simple(node, sh);
		else if (node->type == PIPE)
			execute_pipe(node, sh);
		else if (node->type == REDIR_OUT
			|| node->type == REDIR_IN
			|| node->type == REDIR_APPEND)
			execute_redirection(node, sh);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh->exit_status = WEXITSTATUS(status);
		else
			sh->exit_status = 1;
	}
}

void	execute_ast(t_shell *sh)
{
	if (!sh->ast)
		return ;
	/*if (node_is_builtin(sh->ast))
	{
		execute_builtin(sh->ast, sh);
		return ;
	}*/
	exec_node(sh->ast, sh);
}
