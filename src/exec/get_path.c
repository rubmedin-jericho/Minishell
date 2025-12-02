#include "minishell.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	**get_path_dirs(char **env)
{
	char	*env_path;

	env_path = my_getenv("PATH", env);
	if (!env_path)
		return (NULL);
	return (ft_split(env_path, ':'));
}

static char	*join_path_and_cmd(const char *dir, const char *cmd)
{
	char	*with_slash;
	char	*full;

	with_slash = ft_strjoin(dir, "/");
	if (!with_slash)
		return (NULL);
	full = ft_strjoin(with_slash, cmd);
	free(with_slash);
	return (full);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*find_executable(char *cmd, char **paths)
{
	char	*candidate;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		candidate = join_path_and_cmd(paths[i], cmd);
		if (!candidate)
		{
			i++;
			continue ;
		}
		if (candidate && access(candidate, F_OK | X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*full;

	paths = get_path_dirs(env);
	full = find_executable(cmd, paths);
	ft_free_tab(paths);
	return (full);
}