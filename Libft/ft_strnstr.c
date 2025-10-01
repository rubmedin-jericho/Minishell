/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:03:54 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/14 19:23:21 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	il;

	i = 0;
	il = 0;
	if (little[il] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		il = 0;
		while (little[il] != '\0' && (i + il) < len \
				&& big[i + il] == little[il])
		{
			il++;
			if (little[il] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
//busca un subcadena dentro de una cadena y devuelve //
//un puntero al inicio de esta //
