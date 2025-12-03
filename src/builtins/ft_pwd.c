/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:47:08 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/27 13:56:32 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	shell->exit_status = 0;
}

void	ft_exit(t_shell *shell)
{
	exit(shell->exit_status);
}

void	ft_echo(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_cd(char *next_path, char **env)
{
	int i;
	char *current_path;

	i = 0;
	current_path = getcwd(NULL, 0);
	if(chdir(next_path) == -1)
	{
		perror("cd");
		free(current_path);
		return ;
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", next_path);
		}
		else if(ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", current_path);
		}
		i++;
	}
	free(current_path);
}

/*
void	ft_export()
void	ft_unset()
void	ft_env()
void	exit()
*/
