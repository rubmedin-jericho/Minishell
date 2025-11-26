/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:44:34 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/26 15:44:36 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_last_pipe(t_token *token, t_token **prev_to_pipe)
{
	t_token	*buf;
	t_token	*prev;
	t_token	*last_pipe;

	*prev_to_pipe = NULL;
	buf = token;
	prev = NULL;
	last_pipe = NULL;
	while (buf)
	{
		if (buf->type_tok == T_PIPE)
		{
			last_pipe = buf;
			*prev_to_pipe = prev;
		}
		prev = buf;
		buf = buf->next;
	}
	return (last_pipe);
}

static int	allocate_ast_children(t_ast *ast)
{
	ast->left = malloc(sizeof(t_ast));
	ast->right = malloc(sizeof(t_ast));
	if (!ast->left || !ast->right)
		return (-1);
	ft_memset(ast->left, 0, sizeof(t_ast));
	ft_memset(ast->right, 0, sizeof(t_ast));
	return (0);
}

int	pipe_operator(t_token *token, t_ast *ast)
{
	t_token	*prev_to_last_pipe;
	t_token	*op_token;

	*op_token = find_last_pipe(token, &prev_to_last_pipe);
	*prev_to_last_pipe = NULL;
	if (prev_to_last_pipe)
		prev_to_last_pipe->next = NULL;
	if (!op_token || !op_token->next)
		return (0);
	ast->type = PIPE;
	if (allocate_ast_children(ast) < 0)
		return (-1);
	if (create_ast(token, ast->left) < 0)
		return (-1);
	if (create_ast(op_token->next, ast->right) < 0)
		return (-1);
	return (1);
}
