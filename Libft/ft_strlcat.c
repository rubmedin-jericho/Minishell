/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:55:20 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/15 20:04:00 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *destino, const char *origen, size_t finals)
{
	size_t	sdest;
	size_t	sori;
	size_t	i;

	sdest = ft_strlen(destino);
	sori = ft_strlen(origen);
	i = 0;
	if (finals <= sdest)
		return (finals + sori);
	while (origen[i] && (sdest + i) < (finals -1))
	{
		destino[sdest + i] = origen[i];
		i++;
	}
	destino[sdest + i] = '\0';
	return (sdest + sori);
}
