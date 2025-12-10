/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:00:00 by jmarques          #+#    #+#             */
/*   Updated: 2025/12/10 17:00:02 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal(const char *msg)
{
	perror(msg);
	exit(1);
}

void	free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->type == CMD && node->args)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

t_pipe	init_pipe(t_ast *node, t_shell *sh)
{
	t_pipe	pip;

	pip.node = node;
	pip.sh = sh;
	pip.input_fd = STDIN_FILENO;
	pip.count = 0;
	pip.capacity = 17;
	pip.pipe_fd[0] = -1;
	pip.pipe_fd[1] = -1;
	pip.pids = malloc(sizeof(pid_t) * pip.capacity);
	if (!pip.pids)
		fatal("malloc");
	return (pip);
}
