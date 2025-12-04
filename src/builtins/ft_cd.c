/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:46:14 by rubmedin          #+#    #+#             */
/*   Updated: 2025/12/04 15:46:48 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char *next_path, char **env)
{
	int i;
	char *current_path;

	i = 0;
	current_path = getcwd(NULL, 0);
	if(!current_path)
		return ;
	if(chdir(next_path) == -1)
	{
		perror("cd");
		free(current_path);
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			env[i] = ft_strjoin("PWD=", next_path);
		else if(ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env[i] = ft_strjoin("OLDPWD=", current_path);
		i++;
	}
	printf("TODO BIEN_FINISH\n");
	free(current_path);
}
