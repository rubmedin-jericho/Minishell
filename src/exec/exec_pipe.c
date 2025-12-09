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
/*
static void	child(t_pipe *p)
{
	printf("child\n\n");
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
	printf("parent\n\n");
	close(p->pipe_fd[1]);
	if (p->input_fd != STDIN_FILENO)
		close(p->input_fd);
	execute_pipe_recursive(p->node->right, p->sh, p->pipe_fd[0]);
	close(p->pipe_fd[0]);
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
		close(input_fd);
		return ;
	}
	p.pid = fork();
	if (p.pid < 0)
	{
		perror("fork");
		close(input_fd);
		return ;
	}
	if (p.pid == 0)
		child(&p);
	else
		parent(&p);
}
*/

int	exec_last_cmd(t_ast *node, t_shell *sh, int input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(input_fd);
		return (-1);
	}
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		exec_node_no_fork(node, sh);
		exit(sh->exit_status);
	}
	close(input_fd);
	return (pid);
}

int	execute_pipe_recursive(t_ast *node, t_shell *sh, int input_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (node->type != PIPE)
		return (exec_last_cmd(node, sh, input_fd));
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		close(input_fd);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(input_fd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec_node_no_fork(node->left, sh);
		exit(sh->exit_status);
	}
	close(pipe_fd[1]);
	close(input_fd);
	return (execute_pipe_recursive(node->right, sh, pipe_fd[0]));
}

void free_commands(char **cmds)
{
    int i = 0;
    perror("cmd\n\n");
    if (!cmds)
        return ;
    while (cmds[i])
    {
        free(cmds[i]);
        cmds[i] = NULL;
        i++;
    }

    free(cmds);
    cmds = NULL;
}

void	execute_pipe(t_ast *node, t_shell *sh)
{
	int	status;
	int	last_pid;

	sh->in_pipeline = 1;
	last_pid = execute_pipe_recursive(node, sh, STDIN_FILENO);
	sh->in_pipeline = 0;
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
	free_ast(sh->ast);
}
