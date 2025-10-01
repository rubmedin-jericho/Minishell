/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:30:01 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/16 17:24:01 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resultado;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	resultado = (char *) malloc((len + 1) * sizeof(char));
	if (resultado == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		resultado[i] = s[start];
		start++;
		i++;
	}
	resultado[i] = '\0';
	return (resultado);
}
