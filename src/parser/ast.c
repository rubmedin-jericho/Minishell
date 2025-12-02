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

static int	fill_array(t_token *token, t_ast *ast)
{
	t_token	*buf;
	int		i;
	int		j;

	buf = token;
	i = 0;
	while (buf)
	{
		if (buf->type_tok == T_STRING)
		{
			ast->args[i] = ft_strdup(buf->data);
			if (!ast->args[i])
			{
				j = 0;
				while (j < i)
					free(ast->args[j++]);
				return (-1);
			}
			i++;
		}
		buf = buf->next;
	}
	ast->args[i] = NULL;
	return (1);
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
	ft_memset(ast->args, 0, sizeof(char *) * (count + 1));
	return (fill_array(token, ast));
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
	return (allocate_array(token, ast));
}
