/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:14:46 by rubmedin          #+#    #+#             */
/*   Updated: 2026/01/09 17:05:09 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_array(char **arr, int size)
{
	int	i;
	
	i = 0;
	if (!arr)
		return ;
	if (size == 0)
		while (arr[i])
			free(arr[i++]);
	else
		while (i < size)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
	free(arr);
}

int	getype(char *str, t_flags *flags, t_token *token_v, char **envp)
{
  char *command_path;

  command_path = get_path(str, envp);

	if (is_simple_quoted(str, flags) && !flags->flag_double_quot)
		return (T_SIMPLE_QUOTED);
	else if (is_double_quoted(str, flags) && !flags->flag_simple_quot)
		return (T_DOUBLE_QUOTED);
	else if (is_pipe(str, flags))
		return (T_PIPE);
	else if (is_heredoc(str, flags))
		return (T_HEREDOC);
	else if (is_or_operator(str, flags))
		return (T_FLOW_OPERATOR);
  else if (command_path)
  {
    token_v->path = command_path;
    return (T_COMMAND);
  }
	return (T_STRING);
}

/*Lexer se encarga de tokenizar, categorizar y mirar la sintaxys este bien escrita.*/
int	lexer(t_token **l_tokens, char *str, t_flags *flags, char **envp)
{
	init_list(l_tokens, str, flags, envp);
	print_list(l_tokens);
	return (0);
}
