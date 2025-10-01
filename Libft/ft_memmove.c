/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:02:23 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/15 20:03:24 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *origen, size_t len)
{
	unsigned char		*cdest;
	const unsigned char	*corigen;

	cdest = (unsigned char *)dest;
	corigen = (const unsigned char *)origen;
	if ((!dest && !origen) && (len > 0))
		return (NULL);
	if (corigen < cdest)
	{
		while (len > 0)
		{
			len--;
			cdest[len] = corigen[len];
		}
		return (dest);
	}
	else
	{
		return (ft_memcpy(dest, origen, len));
	}
	return (dest);
}
