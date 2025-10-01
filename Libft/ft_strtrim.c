/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:01:58 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/11 20:59:22 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ver_set(char c, const char *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		i;
	size_t		f;
	size_t		c;
	char		*resultado;

	f = ft_strlen(s1);
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] != '\0' && ver_set(s1[i], set) == 1)
		i++;
	while (f > i && ver_set(s1[f - 1], set) == 1)
		f--;
	resultado = (char *)malloc((f - i + 1) * sizeof(char));
	if (resultado == NULL)
		return (NULL);
	c = 0;
	while (i != f)
	{
		resultado[c] = s1[i];
		c++;
		i++;
	}
	resultado[c] = '\0';
	return (resultado);
}
