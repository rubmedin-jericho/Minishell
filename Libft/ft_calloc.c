/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:42:31 by mregada-          #+#    #+#             */
/*   Updated: 2025/02/08 13:28:32 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*espacio;

	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
	if (((num * size) / num) != size)
		return (NULL);
	espacio = malloc(num * size);
	if (!espacio)
		return (NULL);
	ft_bzero (espacio, num * size);
	return (espacio);
}
