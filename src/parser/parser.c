/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:44:40 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/26 12:44:42 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int allocate_array(t_token *token, t_ast *ast)
{
	int		count;
	t_token	*buf;

	buf = token;
	count = 0;
	while (buf)
	{
		if (buf->type_tok == T_STRING)
			count++;
		buf = buf->next;
	}
	if (count == 0)
		return (0);
	ast->args = malloc(sizeof(char *) * (count + 1));
	if (!ast->args)
		return (-1);
	return (1);
}

int	init_ast(t_token *token, t_ast *ast)
{
	t_token	*buf;
	int		i;
	int		ret;

	if (!token || !ast)
		return (-1);
	ast->type = CMD;
	ast->left = NULL;
	ast->right = NULL;
	ast->file = NULL;
	ast->args = NULL;
	ret = allocate_array(token, ast);
	if (ret == -1)
		return (-1);
	if (ret == 0)
		return (0);
	buf = token;
	i = 0;
	while (buf)
	{
		if (buf->type_tok == T_STRING)
		{
			ast->args[i] = ft_strdup(buf->data);
			i++;
		}
		buf = buf->next;
	}
	ast->args[i] = NULL;
	return (0);
}

int pipe_operator(t_token *token, t_ast *ast)
{
	t_token	*buf;
	t_token	*op_token;
	t_token *prev = NULL;
	t_token *prev_to_last_pipe = NULL;
	buf = token;
	op_token = NULL;
	//get the last pipe operator
	while (buf)
	{
		if (buf->type_tok == T_PIPE)
		{
			op_token = buf;
			prev_to_last_pipe = prev;
		}
	    prev = buf;
		buf = buf->next;
	}
	if (prev_to_last_pipe)
		prev_to_last_pipe->next = NULL;
	//check if i get the pipe and the pipe is not the last
	if (!op_token || !op_token->next)
		return (0);
	//setup AST node
	ast->type = PIPE;
	ast->args = NULL;
	ast->file = NULL;
	ast->left = malloc(sizeof(t_ast));
	ast->right = malloc(sizeof(t_ast));
	if (!ast->left || !ast->right)
		return (-1);
	memset(ast->left, 0, sizeof(t_ast));
	memset(ast->right, 0, sizeof(t_ast));
	if (create_ast(token, ast->left) < 0) 
		return (-1);
	if (create_ast(op_token->next, ast->right) < 0)
		return (-1);
	return (1);
}

int	redirection(t_token *token, t_ast *ast)
{
	t_token	*buf;

	buf = token;
	while (buf)
	{
		if (buf->type_tok == T_APPEND)
		{
			ast->type = REDIR_IN;
			if (ft_strncmp(buf->data, ">", 2) == 0)
				ast->type = REDIR_OUT;
			ast->args = NULL;
			ast->left = malloc(sizeof(t_ast));
			if (!ast->left)
				return (-1);
			if (create_ast(token, ast->left) < 0)
				return (-1);	
			ast->right = NULL;
			if (buf->next && buf->next->type_tok == T_STRING)
				ast->file = ft_strdup(buf->next->data);
			return (1);
		}
		buf = buf->next;
	}
	return (0);
}

static int fill_command_node(t_token *token, t_ast *ast)
{
    t_token *buf;
    int count = 0;
    int i;

    if (!token || !ast)
        return -1;

    ast->type = CMD;
    ast->left = NULL;
    ast->right = NULL;
    ast->file = NULL;
    ast->args = NULL;

    // Count string tokens
    buf = token;
    while (buf)
    {
        if (buf->type_tok == T_STRING)
            count++;
        buf = buf->next;
    }

    if (count == 0)
        return 0;

    ast->args = malloc(sizeof(char *) * (count + 1));
    if (!ast->args)
        return -1;

    i = 0;
    buf = token;
    while (buf)
    {
        if (buf->type_tok == T_STRING)
            ast->args[i++] = ft_strdup(buf->data);
        buf = buf->next;
    }
    ast->args[i] = NULL;

    return 0;
}

int create_ast(t_token *token, t_ast *ast)
{
	int	ret;

	if (!token || !ast)
		return (-1);
	ret = pipe_operator(token, ast);
	if (ret != 0)
	{
		if (ret == 1)
			return (0);
		return (-1);
	}	
	ret = redirection(token, ast);
	if (ret != 0)
	{
		if (ret == 1)
			return (0);
		return (-1);
	}
	return (fill_command_node(token, ast));
}

int	parser(t_token *token, t_ast *ast)
{
	if (create_ast(token, ast))
	{
		return (0);
	}
	return (1);
}
