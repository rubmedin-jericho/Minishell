/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:25:47 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/14 17:35:11 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *buffer, int c, size_t n)
{
	unsigned char			v;
	size_t					i;
	const unsigned char		*str;

	i = 0;
	str = (const unsigned char *)buffer;
	v = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == v)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
