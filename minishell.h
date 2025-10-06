#ifndef MINISHELL_H
# define MINISHELL_H

/*----LIBRERY----*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

/*----COLORS----*/
# define COLOR_RED "\x1b[31m"
# define COLOR_GOLD "\x1b[38;5;220m"
# define COLOR_RESET "\x1b[0m"

/*----MACROS----*/
#define MINISHELL_BANNER COLOR_GOLD "\n\
                 \\__|          \\__| $$$$$$\\  $$ |                $$ |$$ |\n\
   $$$$$$\\$$$$\\  $$\\ $$$$$$$\\  $$\\ $$  __$$\\ $$$$$$$\\   $$$$$$\\  $$ |$$ |\n\
   $$  _$$  _$$\\ $$ |$$  __$$\\ $$ |$$ /  \\__|$$  __$$\\ $$  __$$\\ $$ |$$ |\n\
   $$ / $$ / $$ |$$ |$$ |  $$ |$$ |\\$$$$$$\\  $$ |  $$ |$$$$$$$$ |$$ |$$ |\n\
   $$ | $$ | $$ |$$ |$$ |  $$ |$$ | \\____$$\\ $$ |  $$ |$$   ____|$$ |$$ |\n\
   $$ | $$ | $$ |$$ |$$ |  $$ |$$ |$$\\   $$ |$$ |  $$ |\\$$$$$$$\\ $$ |$$ |\n\
   \\__| \\__| \\__|\\__|\\__|  \\__|\\__|\\$$$$$$  |\\__|  \\__| \\_______|\\__|\\__|\n\
                                    \\______/                             \n\
\n" COLOR_RESET

/*----STRUCTS----
 * ESTE ES UN ENUM PARA SELECCIONAR EL TIPO DE TOKEN QUE ES PARA EVITAR TENER MUCHOS IF COMPARANDO QUE ES.
 * FUNCION EN PROGRESO.
 * */
typedef enum	s_type
{
				T_INPUT,
				T_OUTPUT,
				T_APPEND,
				T_HEREDOC,
				T_PIPE,
}				t_type;

/*ESTA ES LA STRUCT PARA GUARDAR LOS TOKENS*/
typedef struct	s_token
{
	char		*data;
	t_type		lexer;
	struct 		s_token *next;
}				t_token;

/*----FUNCTIONS----*/
int		lexer(t_token **l_tokens, char *str);
char	**ft_split(char const *s, char c);
char	*asignar_palabra(const char *s, int len);
#endif
