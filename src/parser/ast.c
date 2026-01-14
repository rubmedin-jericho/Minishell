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

/*
 * fill the array with the values of the input
 */
static int	fill_array(t_token *token, t_ast *ast)
{
	t_token	*buf;
	int		i;

	buf = token;
	i = 0;
	while (buf)
	{
		if (buf->type_tok == T_STRING)
		{
			ast->args[i] = ft_strdup(buf->data);
			if (!ast->args[i])
			{
				while (i-- >= 0)
					free(ast->args[i]);
				ast->args = NULL;
				return (-1);
			}
			i++;
		}
		buf = buf->next;
	}
	ast->args[i] = NULL;
	return (0);
}

/*
 * create a new array of string to put the value
 */
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
	ast->args = ft_calloc(count + 1, sizeof(char *));
	if (!ast->args)
		return (-1);
	if (fill_array(token, ast) < 0)
	{
		free(ast->args);
		ast->args = NULL;
		return (-1);
	}
	return (0);
}

static void	init_ast(t_ast *ast)
{
	if (!ast)
		return ;
	ast->type = T_STRING;
	ast->left = NULL;
	ast->right = NULL;
	ast->file = NULL;
	ast->args = NULL;
}

/*
 * check what type of return received
 * ret = 0 nothing is created
 * ret = 1 created
 * ret = -1 error
 */
static int	check_ret(int ret)
{
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (0);
	return (1);
}

int	create_ast(t_token *token, t_ast *ast)
{
	int	ret;

	if (!token || !ast)
		return (-1);
	init_ast(ast);
	ret = pipe_operator(token, ast);
	ret = check_ret(ret);
	if (ret != 1)
		return (ret);
	ret = redirection(token, ast);
	ret = check_ret(ret);
	if (ret != 1)
		return (ret);
	return (allocate_array(token, ast));
}
