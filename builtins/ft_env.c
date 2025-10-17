/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:53:47 by mregada-          #+#    #+#             */
/*   Updated: 2025/10/17 18:53:50 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	ft_env(t_base *base)
{
	int i;

	i = 0;
	while(base->envp[i])
	{
		if (ft_strchr(base->envp[i], '='))
			printf("%s\n",base->envp[i++]);
	}
	return (1);
}