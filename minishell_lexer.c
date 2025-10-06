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

static void adding_token(t_token **l_tokens, t_token *token)
{
	t_token *buff_token;

	if (!*l_tokens)
	{
		token->next = NULL; 
		*l_tokens = token;
		return ;
	}
	buff_token = *l_tokens;
	while (buff_token->next)
		buff_token = buff_token->next;
	buff_token->next = token;
	token->next = NULL;
}

static t_token *create_token(char *str)
{
	t_token *buff_tmp;
	(void)str;

	buff_tmp = malloc(sizeof(t_token));
	if(!buff_tmp)
		return NULL;
	buff_tmp->data = "hola";
	buff_tmp->lexer = T_OUTPUT;
	return (buff_tmp);
}

static void	init_list_token(t_token **tokens, char *str)
{
	t_token *buff_tmp;
	int i;
	(void)str;

	i = 0;
	while(i < 7)
	{ 
		buff_tmp = create_token(str);
		if(!buff_tmp)
			return ;
		adding_token(tokens, buff_tmp);
		i++;
	}
}

static void print_list(t_token **l_tokens)
{
	t_token *buff_token;

	if (!*l_tokens)
		exit(1);
	buff_token = *l_tokens;
	while(buff_token)
	{
		printf(" data: %s\n lexer: %i\n", buff_token->data, buff_token->lexer);
		buff_token = buff_token->next;
	}
}

/*Lexer se encarga de tokenizar, categorizar y mirar la sintaxys este bien escrita.*/
int	lexer(t_token **l_tokens, char *str)
{
	init_list_token(l_tokens, str);
	print_list(l_tokens);
	return (0);
}
