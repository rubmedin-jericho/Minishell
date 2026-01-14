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

/*
 * get the last pipe
 */
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

/*
 * set memory allocation for left and right side of the tree
 */
static int	allocate_ast_children(t_ast *ast)
{
	ast->left = ft_calloc(1, sizeof(t_ast));
	if (!ast->left)
		return (-1);
	ast->right = ft_calloc(1, sizeof(t_ast));
	if (!ast->right)
	{
		free(ast->left);
		ast->left = NULL;
		return (-1);
	}
	return (0);
}

static t_token	*split_on_pipe(t_token *token, t_token **prev,
	t_token **saved_next)
{
	t_token	*pipe;

	if (!token || token->type_tok == T_PIPE)
		return (NULL);
	*saved_next = NULL;
	pipe = find_last_pipe(token, prev);
	if (!pipe || !pipe->next || pipe->next->type_tok == T_PIPE)
		return (NULL);
	if (*prev)
	{
		*saved_next = (*prev)->next;
		(*prev)->next = NULL;
	}
	return (pipe);
}

/*
 * create a new Abstract Syntax Tree (AST)
 * ret = 0 no ast created
 * ret = 1 ast created
 * ret = -1 error creating the ast
 */
int	create_ast_safe(t_token *token, t_ast *child,
						t_token *prev, t_token *saved_link)
{
	int	ret;

	ret = create_ast(token, child);
	if (ret < 0)
	{
		free_ast(child);
		if (prev)
			prev->next = saved_link;
		return (-1);
	}
	return (ret);
}

/*
 * finds the first | token
 * prev points to the token before the |
 * saved_next points to the token after the |
 * disconnects the | from the list for parsing
 * left/right branches
 * return = 0 -> no pipe found
 * return = 1 -> pipe parsed successfully
 * return = -1 -> error
 */
int	pipe_operator(t_token *token, t_ast *ast)
{
	t_token	*prev;
	t_token	*pipe;
	t_token	*saved_next;
	int		ret;

	pipe = split_on_pipe(token, &prev, &saved_next);
	if (!pipe)
		return (0);
	ast->type = T_PIPE;
	if (allocate_ast_children(ast) < 0)
	{
		if (prev)
			prev->next = saved_next;
		return (-1);
	}
	ret = create_ast_safe(token, ast->left, prev, saved_next);
	if (ret < 0)
	{
		free_ast(ast->right);
		return (-1);
	}
	ret = create_ast_safe(pipe->next, ast->right, prev, saved_next);
	if (ret < 0)
	{
		free_ast(ast->left);
		return (-1);
	}
	return (1);
}
