/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:14:46 by rubmedin          #+#    #+#             */
/*   Updated: 2025/10/02 15:15:02 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_cmd *command, char *str)
{
	int i;

	i = 0;
	command->tokens = ft_split(str, ' ');
	if(!command->tokens)
		return (1);
	while(command->tokens[i])
	{
		printf("%s\n", command->tokens[i]);
		i++;
	}
	return (0);
}
