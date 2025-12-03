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

static void	child(t_pipe *p)
{
	close(p->pipe_fd[0]);
	if (p->input_fd != STDIN_FILENO)
	{
		dup2(p->input_fd, STDIN_FILENO);
		close(p->input_fd);
	}
	dup2(p->pipe_fd[1], STDOUT_FILENO);
	close(p->pipe_fd[1]);
	exec_node_no_fork(p->node->left, p->sh);
	exit(EXIT_FAILURE);
}

static void	parent(t_pipe *p)
{
	close(p->pipe_fd[1]);
	if (p->input_fd != STDIN_FILENO)
		close(p->input_fd);
	execute_pipe_recursive(p->node->right, p->sh, p->pipe_fd[0]);
	waitpid(p->pid, NULL, 0);
}

static void	run_pipe(t_ast *node, t_shell *sh, int input_fd)
{
	t_pipe	p;

	p.node = node;
	p.sh = sh;
	p.input_fd = input_fd;
	if (pipe(p.pipe_fd) < 0)
	{
		perror("pipe");
		return ;
	}
	p.pid = fork();
	if (p.pid < 0)
	{
		perror("fork");
		return ;
	}
	if (p.pid == 0)
		child(&p);
	else
		parent(&p);
}

void	execute_pipe_recursive(t_ast *node, t_shell *sh, int input_fd)
{
	pid_t	pid;

	if (!node)
		return ;
	if (node->type != PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			exec_node_no_fork(node, sh);
			exit(EXIT_FAILURE);
		}
		close(input_fd);
		waitpid(pid, NULL, 0);
		return ;
	}
	run_pipe(node, sh, input_fd);
}

void	execute_pipe(t_ast *node, t_shell *sh)
{
	sh->in_pipeline = 1;
	execute_pipe_recursive(node, sh, STDIN_FILENO);
	sh->in_pipeline = 0;
}
