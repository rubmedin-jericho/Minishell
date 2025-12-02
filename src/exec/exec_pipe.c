/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:29:43 by jmarques          #+#    #+#             */
/*   Updated: 2025/12/02 13:29:47 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_ast *node, t_shell *sh, int input_fd, int *fd)
{
	close(fd[0]);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

int	pipe(t_ast *node, t_shell *sh, int input_fd, int *fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		child(node, sh, input_fd, fd);
	else
	{
		close(fd[1]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		execute_pipe_recursive(node->right, sh, fd[0]);
		waitpid(pid, &status, 0);
	}
	return (0);
}

void	execute_pipe_recursive(t_ast *node, t_shell *sh, int input_fd)
{
	int	fd[2];

	if (!node)
		return ;
	if (node->type != PIPE)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		exec_node(node, sh);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pipe(*node, *sh, input_fd, fd);
}

void	execute_pipe(t_ast *node, t_shell *sh)
{
	execute_pipe_recursive(node, sh, STDIN_FILENO);
}
