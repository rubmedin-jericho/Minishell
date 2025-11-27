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

static t_token	*find_redirection(t_token *token, t_token **prev_to_redir)
{
	t_token	*buf;
	t_token	*prev;

	buf = token;
	prev = NULL;
	*prev_to_redir = NULL;
	while (buf)
	{
		if (buf->type_tok == T_HEREDOC)
		{
			*prev_to_redir = prev;
			return (buf);
		}
		prev = buf;
		buf = buf->next;
	}
	return (NULL);
}

static int	get_redir_type(t_token *redir)
{
	if (ft_strncmp(redir->data, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(redir->data, ">>", 3) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(redir->data, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(redir->data, "<<", 3) == 0)
		return (REDIR_HEREDOC);
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
	t_token	*prev_to_redir;
	t_token	*redir;

	prev_to_redir = NULL;
	redir = find_redirection(token, &prev_to_redir);
	if (!redir || !redir->next)
		return (0);
	if (prev_to_redir)
		prev_to_redir->next = NULL;
	ast->type = get_redir_type(redir);
	ast->file = ft_strdup(redir->next->data);
	if (!ast->file)
		return (-1);
	if (allocate_left_ast(ast) < 0)
		return (-1);
	if (create_ast(token, ast->left) < 0)
		return (-1);
	return (1);
}
