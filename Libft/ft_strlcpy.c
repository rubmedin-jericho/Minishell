/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:55:18 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:25 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *destino, const char *origen, size_t sdest)
{
	size_t	sorigen;
	size_t	i;

	sorigen = 0;
	i = 0;
	while (origen[sorigen] != '\0')
		sorigen ++;
	if (sdest == 0)
		return (sorigen);
	while (i < (sdest - 1) && origen[i] != '\0')
	{
		destino[i] = origen[i];
		i++;
	}
	destino[i] = '\0';
	return (sorigen);
}
