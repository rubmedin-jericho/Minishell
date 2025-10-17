/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:41:22 by mregada-          #+#    #+#             */
/*   Updated: 2025/10/17 19:41:23 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ft_exit(t_base *base, char **args, int is_child)
{
	int	code;

	code = base->exit_status;
	if (args[1])
		code = ft_atoi(args[1]);
	if(is_child)
		exit(code);
	else
	{
		base->exit_status = code;
		clear_and_leave(base, args);
	}
}