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

void	exec_input(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_RDONLY);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

void	exec_output(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_node(node->left, sh);
	exit(EXIT_FAILURE);
}

void	exec_append(t_ast *node, t_shell *sh)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(node->file);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
