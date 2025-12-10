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
		if (curr->type_tok == REDIR_IN || curr->type_tok == REDIR_OUT
			|| curr->type_tok == REDIR_APPEND || curr->type_tok == T_HEREDOC)
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

static int	get_redir_type(t_token *redir)
{
	if (redir->data[0] == '>' && redir->data[1] == '>')
		return (REDIR_APPEND);
	else if (redir->data[0] == '>')
		return (REDIR_OUT);
	else if (redir->data[0] == '<' && redir->data[1] == '<')
		return (T_HEREDOC);
	else if (redir->data[0] == '<')
		return (REDIR_IN);
	return (-1);
}

static int	allocate_left_ast(t_ast *ast)
{
	ast->left = malloc(sizeof(t_ast));
	if (!ast->left)
		return (-1);
	ft_memset(ast->left, 0, sizeof(t_ast));
	return (0);
}

int	redirection(t_token *token, t_ast *ast)
{
	t_token	*prev;
	t_token	*redir;

	prev = NULL;
	redir = find_redirection(token, &prev);
	if (!redir || !redir->next)
		return (0);
	ast->type = get_redir_type(redir);
	ast->file = ft_strdup(redir->next->data);
	if (!ast->file)
		return (-1);
	if (prev)
		prev->next = redir->next->next;
	else
		token = redir->next->next;
	if (allocate_left_ast(ast) < 0)
		return (-1);
	if (create_ast(token, ast->left) < 0)
		return (-1);
	return (1);
}
