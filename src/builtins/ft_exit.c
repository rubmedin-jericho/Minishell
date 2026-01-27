/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:39:21 by rubmedin          #+#    #+#             */
/*   Updated: 2025/12/04 15:39:32 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exit(t_shell *shell)
{
	int	i;
	int	is_number;

	shell->exit_status = 127;
	if (!shell->ast || !shell->ast->args[1])
	{
		free_ast(shell->ast);
		free_env(shell->envp);
		free_tokens(shell);
		free(shell->str);
		exit(shell->exit_status);
	}
	i = 0;
	while (shell->ast->args[1][i] != '\0')
	{
		is_number = 1;
		if (!ft_isdigit(shell->ast->args[1][i]))
		{
			is_number = 0;
			break ;
		}
		i++;
	}
	if (is_number == 1)
		shell->exit_status = ft_atoi(shell->ast->args[1]);
	free_ast(shell->ast);
	free_env(shell->envp);
	free_tokens(shell);
	free(shell->str);
	exit(shell->exit_status);
}
