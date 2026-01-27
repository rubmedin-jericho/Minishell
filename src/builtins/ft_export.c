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

#include "minishell.h"

static int	ft_length_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	find_env(char **envp, char *name)
{
	int		i;
	int		len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len)
			&& envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	valid_identifier(char *s)
{
	int		i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	new_envp(t_shell *shell, char *arg)
{
	int		len;
	char	**tmp;

	len = ft_length_env(shell->envp);
	tmp = realloc(shell->envp, sizeof(char *) * (len + 2));
	if (!tmp)
		return ;
	shell->envp = tmp;
	shell->envp[len] = ft_strdup(arg);
	shell->envp[len + 1] = NULL;
}

void	ft_export(t_shell *shell)
{
	int		idx;
	int		i;

	if (!shell || !shell->envp || !shell->ast
		|| !shell->ast->args || !shell->ast->args[1])
		return ;
	i = 0;
	while (shell->ast->args[++i])
	{
		if (!valid_identifier(shell->ast->args[i]))
		{
			write(2, "export: not a valid identifier\n", 31);
			continue ;
		}
		idx = find_env(shell->envp, shell->ast->args[i]);
		if (idx != -1)
		{
			free(shell->envp[idx]);
			shell->envp[idx] = ft_strdup(shell->ast->args[i]);
			continue ;
		}
		new_envp(shell, shell->ast->args[i]);
	}
}
