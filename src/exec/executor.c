/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarques <jmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:19:54 by jmarques          #+#    #+#             */
/*   Updated: 2025/11/27 14:19:56 by jmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == 0)
		ret = open(file, O_RDONLY);
	else if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		error();
	if (ret == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
		error("invalid command");
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		free_tab(cmd);
		error();
	}
	execve(path, cmd, envp);
	free(path);
	free_tab(cmd);
	error("execve failed");
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	exec()
{
	int	i;
	int	fileout;
	int	filein;

	i = 2;
	filein = open_file(argv[argc - 1], 0);
	fileout = open_file(argv[1], 1);
	dup2(filein, STDIN_FILENO);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}