/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:14:46 by rubmedin          #+#    #+#             */
/*   Updated: 2025/10/07 18:39:17 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	free_array(char **arr, int size)
{
	int	i;
	
	i = 0;
	if (!arr)
		return ;
	if (size == 0)
		while (arr[i])
		{
			//printf("FREE arr[%d] %p (%s)\n", i, arr[i], arr[i]);
			free(arr[i++]);
		}
	else
		while (i < size)
		{
			if (arr[i])
			{
				//printf("FREE arr[%d] %p (%s)\n", i, arr[i], arr[i]);
				free(arr[i]);
			}
			i++;
		}
	//printf("FREE arr %p\n", arr);
	free(arr);
}
/*funcion que comprueba si es ejecutable*/
static char	*check_paths(char *cmd, char **paths)
{
	char	*joined = NULL;
	char	*full_path = NULL;
	int		i;
	i = 0;
	
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");// "/usr/bin"+ "/"
		full_path = ft_strjoin(joined, cmd);// /usr/bin/ls
		if (joined != full_path)
		{
			free(joined);
		}
		if (access(full_path, X_OK) == 0)//si es ejecutable
		{
			//printf("FREE_ARRAY paths %p\n", paths);
			free_array(paths, 0);//se libera el array de strings paths del split
			//printf("RETURNING full_path %p\n", full_path);
			return (full_path);//devolvemos ruta valida
		}
		free(full_path);//liberamos full_path no ejecutable
		i++;
	}
	return (NULL);
}
/* Funcion que busca la ruta del ejecutable del comando*/
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++; // situamos el puntero en la linea que contiene PATH=/usr/local/bin:/usr/bin:/bin
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');//guardamos array de strings con los paths
	if (!paths)//array ={/usr/local/bin, /usr/bin , /bin, NULL}
		return (NULL);
	full_path = check_paths(cmd, paths);
	if (!full_path)
	{
		free_array(paths, 0);
		return (NULL);
	}
	return (full_path);
}

int	getype(char *str, char **enp)
{
	char *exist_path;

	exist_path = get_cmd_path(str, enp);
	if(exist_path)
		return (T_COMMAND);	
	return (T_STRING);
}

/*Lexer se encarga de tokenizar, categorizar y mirar la sintaxys este bien escrita.*/
int	lexer(t_token **l_tokens, char *str)
{
	int	count;

	count = ft_count_word(str, ' ');
	init_list_token(l_tokens, str, count);
	print_list(l_tokens);
	return (0);
}
