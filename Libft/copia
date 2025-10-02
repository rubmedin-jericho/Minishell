/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:27:21 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/17 18:50:49 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contador_letras_comis(char const *s, char c)
{
	int	letras;
	int	comi_simple;
	int	comi_doble;

	letras = 0;
	comi_simple = 0;
	comi_doble = 0;
	while (s[letras])
	{
		if (s[letras] == '\'' && !comi_doble)
			comi_simple = 1 - comi_simple;
		else if (s[letras] == '\"' && !comi_simple)
			comi_doble = 1 - comi_doble;
		if (s[letras] == c && !comi_doble && !comi_simple)
			break ;
		letras++;
	}
	return (letras);
}

static int	contador_palabras_comis(char const *s, char c)
{
	int	num;
	int	palabra_flag;
	int	comi_simple;
	int	comi_doble;

	num = 0;
	palabra_flag = 0;
	comi_simple = 0;
	comi_doble = 0;
	while (*s != '\0')
	{
		if (*s == '\'' && !comi_doble)
			comi_simple = 1 - comi_simple;
		else if (*s == '\"' && !comi_simple)
			comi_doble = 1 - comi_doble;
		if (*s != c && !palabra_flag)
		{
			palabra_flag = 1;
			num++;
		}
		else if (*s == c && !comi_doble && !comi_simple)
			palabra_flag = 0;
		s++;
	}
	return (num);
}

static char	*asignar_palabra(const char *s, int len)
{
	char	*palabra;
	int		i;
	int		j;
	int		desp;

	desp = 0;
	if ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"'))
	{
		desp = 1;
		len -= 2;
	}
	palabra = malloc((len + 1) * sizeof(char));
	if (palabra == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		palabra[j++] = s[i + desp];
		i++;
	}
	palabra[j] = '\0';
	return (palabra);
}

static int	analizar_palabras(char const*s, char c, char **resultado)
{
	int		si;
	int		len_letras;
	size_t	ri;

	si = 0;
	ri = 0;
	while (s[si])
	{
		while (s[si] == c)
			si++;
		if (s[si] == '\0')
			break ;
		len_letras = contador_letras_comis(&s[si], c);
		resultado[ri] = asignar_palabra(&s[si], len_letras);
		if (!resultado[ri])
			return (ri);
		ri++;
		si = si + len_letras;
	}
	resultado[ri] = NULL;
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**resultado;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	n = contador_palabras_comis(s, c);
	resultado = malloc((n + 1) * sizeof(char *));
	if (!resultado)
		return (NULL);
	i = analizar_palabras (s, c, resultado);
	if (i != -1)
	{
		n = 0;
		while (n < i)
			free (resultado[n++]);
		free (resultado);
		return (NULL);
	}
	return (resultado);
}
