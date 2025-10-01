/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:46:24 by mregada-          #+#    #+#             */
/*   Updated: 2024/09/30 17:41:12 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char	*src)
{
	size_t		len;
	char		*copia;
	size_t		i;

	len = 0;
	i = 0;
	while (src[len] != '\0')
		len++;
	copia = malloc(len + 1);
	if (copia == NULL)
		return (NULL);
	while (i < len)
	{
		copia[i] = src[i];
		i++;
	}
	copia[len] = '\0';
	return (copia);
}
