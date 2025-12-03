/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:29:54 by jmarques          #+#    #+#             */
/*   Updated: 2025/12/02 13:29:56 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_fd(int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	exec_input(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	redirect_fd(fd);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

void	exec_output(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	redirect_fd(fd);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

void	exec_append(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	redirect_fd(fd);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

void	execute_redirection(t_ast *node, t_shell *sh)
{
	if (!node)
		return ;
	if (node->type == REDIR_IN)
		exec_input(node, sh);
	else if (node->type == REDIR_OUT)
		exec_output(node, sh);
	else if (node->type == REDIR_APPEND)
		exec_append(node, sh);
}
