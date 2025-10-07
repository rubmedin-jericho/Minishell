/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:14:46 by rubmedin          #+#    #+#             */
/*   Updated: 2025/10/07 18:39:21 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Lexer se encarga de tokenizar, categorizar y mirar la sintaxys este bien escrita.*/
int	lexer(t_token **l_tokens, char *str)
{
	int	count;

	count = ft_count_word(str, ' ');
	init_list_token(l_tokens, str, count);
	print_list(l_tokens);
	return (0);
}
