/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:30:34 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/11 21:00:28 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int i, char c))
{
	unsigned int	i;
	char			*resultado;

	i = 0;
	if (s == NULL)
		return (NULL);
	resultado = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (resultado == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		resultado[i] = (*f)(i, s[i]);
		i++;
	}
	resultado[i] = '\0';
	return (resultado);
}
