/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:57:38 by mregada-          #+#    #+#             */
/*   Updated: 2025/10/17 19:57:40 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_and_leave(t_base *base, char **args)
{
	free2d(args);
	free2d(base->envp);
	rl_clear_history();//Borra historial completo y libera la memoria
	exit(base->exit_status);
}