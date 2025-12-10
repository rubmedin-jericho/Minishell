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

void	ft_cd(char *next_path, t_shell **shell)
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
	while ((*shell)->envp[i])
	{
		if (ft_strncmp((*shell)->envp[i], "PWD=", 4) == 0)
		{
			free((*shell)->envp[i]);
			(*shell)->envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		else if(ft_strncmp((*shell)->envp[i], "OLDPWD=", 7) == 0)
		{
			free((*shell)->envp[i]);
			(*shell)->envp[i] = ft_strjoin("OLDPWD=", current_path);
		}
		i++;
	}
	free(current_path);
}
