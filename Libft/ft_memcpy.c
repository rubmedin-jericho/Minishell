/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:27:16 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/15 19:44:17 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t i)
{
	size_t				c;
	unsigned char		*cdest;
	const unsigned char	*csrc;

	c = 0;
	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	if (!dest && !src)
	{
		return (NULL);
	}
	while (c < i)
	{
		cdest[c] = csrc[c];
		c++;
	}
	return (dest);
}
