/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubmedin <rubmedin@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:25:43 by rubmedin          #+#    #+#             */
/*   Updated: 2025/09/29 16:25:11 by rubmedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str;

	printf(MINISHELL_BANNER);
	while(1)
	{
		str = readline("minishell> "); //La funcion readline(const char *str) es la que te lee el stdin(salida estandar del input) y te lo guarda en str.
		if(str)
			add_history(str);
		printf("%s\n", str);
		free(str);
	}
	return (0);
}

/*	Uso readline porque la otra opcion seria read y usar read seria poner mas trabajo porque read tiene la limitacion de leer
 *
 *
 *
 * */
