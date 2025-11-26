/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:23:32 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/26 15:31:16 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_array(t_token *token, t_ast *ast)
{
	t_token	*buf;
	int		i;

	buf = token;
	i = 0;
	while (buf)
	{
		if (buf->type_tok == T_STRING)
			ast->args[i++] = ft_strdup(buf->data);
		buf = buf->next;
	}
	ast->args[i] = NULL;
}

static int	allocate_array(t_token *token, t_ast *ast)
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
	fill_array(token, ast);
	return (1);
}

int	init_ast(t_ast *ast)
{
	if (!ast)
		return (-1);
	ast->type = CMD;
	ast->left = NULL;
	ast->right = NULL;
	ast->file = NULL;
	ast->args = NULL;
	return (0);
}

int	create_ast(t_token *token, t_ast *ast)
{
	int	ret;

	if (!token || !ast)
		return (-1);
	init_ast(ast);
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
