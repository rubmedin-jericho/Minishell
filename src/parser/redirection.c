/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:09 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/26 16:00:10 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_redirection(t_token *token, t_token **prev_to_redir)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*last;
	t_token	*last_prev;

	curr = token;
	prev = NULL;
	last_prev = NULL;
	last = NULL;
	*prev_to_redir = NULL;
	while (curr)
	{
		if (curr->type_tok >= T_REDIR_OUT && curr->type_tok <= T_HEREDOC)
		{
			last = curr;
			last_prev = prev;
		}
		prev = curr;
		curr = curr->next;
	}
	*prev_to_redir = last_prev;
	return (last);
}

static int	allocate_left_ast(t_ast *ast)
{
	ast->left = malloc(sizeof(t_ast));
	if (!ast->left)
		return (-1);
	ft_memset(ast->left, 0, sizeof(t_ast));
	return (0);
}

static int	extract_redirection(t_token **token, t_ast *ast,
								t_token **prev, t_token **saved_next)
{
	t_token	*redir;

	*prev = NULL;
	*saved_next = NULL;
	redir = find_redirection(*token, prev);
	if (!redir)
		return (0);
	if (!redir->next || redir->next->type_tok != T_STRING)
		return (-1);
	ast->type = redir->type_tok;
	ast->file = ft_strdup(redir->next->data);
	if (!ast->file)
		return (-1);
	if (*prev)
	{
		*saved_next = (*prev)->next;
		(*prev)->next = redir->next->next;
	}
	else
	{
		*saved_next = *token;
		*token = redir->next->next;
	}
	return (1);
}

int	error_redirect(t_token **token, t_ast *ast,
					t_token **prev, t_token **saved_next)
{
	if (*prev)
		(*prev)->next = *saved_next;
	else
		*token = *saved_next;
	free(ast->file);
	ast->file = NULL;
	return (-1);
}

int	redirection(t_token *token, t_ast *ast)
{
	t_token	*prev;
	t_token	*saved_next;
	int		ret;

	ret = extract_redirection(&token, ast, &prev, &saved_next);
	if (ret <= 0)
		return (ret);
	if (allocate_left_ast(ast) < 0)
		return error_redirect(&token, ast, &prev, &saved_next);
	ret = create_ast(token, ast->left);
	if (ret < 0)
		return error_redirect(&token, ast, &prev, &saved_next);
	if (prev)
		prev->next = saved_next;
	else
		token = saved_next;
	return (1);
}