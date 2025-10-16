/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_simple_quot.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:53:37 by rubmedin          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:28 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_simple_quoted(char *str, int *flag_quot)
{
	int	iter;

	iter = 0;
	while(str[iter])
	{
		if (str[iter] == '\'' && *flag_quot == 0)
		{
			*flag_quot = 1;
			return (1);
		}
		else if (str[iter] == '\'' && *flag_quot == 1)
		{
			*flag_quot = 0;
			return (1);
		}
		else if  (*flag_quot == 1)
			return (1);
		iter++;
	}
	return (0);
}

int	is_double_quoted(char *str, int *flag_quot)
{
	int	iter;

	iter = 0;
	while(str[iter])
	{
		if (str[iter] == '\"' && *flag_quot == 1)
		{
			*flag_quot = 2;
			return (1);
		}
		else if (str[iter] == '\"' && *flag_quot == 2)
		{
			*flag_quot = 0;
			return (1);
		}
		else if (*flag_quot == 2)
			return (2);
		iter++;
	}
	return (0);
}

int	is_pipe(char *str)
{
	int	iter;

	iter = 0;
	while(str[iter])
	{
		if (str[iter] == '|')
			return (1);
		iter++;
	}
	return (0);
}
