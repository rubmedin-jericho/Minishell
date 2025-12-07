/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:45:50 by rubmedin          #+#    #+#             */
/*   Updated: 2025/12/07 20:59:42 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_lenght_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	return (0);
}

void	ft_export(char *str, char **env)
{
	char	**cpy_env;
	int		lenght_env;
	
	lenght_env = ft_lenght_env(env);
	cpy_env = env;
	env = malloc(sizeof(char *) * lenght_env + 2);	

	
}
