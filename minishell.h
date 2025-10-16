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

/* ─── COLORES DE TEXTO ────────────────────────────────*/
# define COLOR_GOLD "\x1b[38;5;220m"
# define COLOR_BLACK   "\x1b[30m"
# define COLOR_RESET "\x1b[0m"
# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"
# define COLOR_WHITE   "\x1b[37m"


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
				T_STRING, /*---0---*/
				T_SIMPLE_QUOTED, /*---1---*/
				T_DOUBLE_QUOTED, /*---2---*/
				T_APPEND, /*---3---*/
				T_COMMAND, /*---4---*/
				T_HEREDOC, /*---5---*/
				T_PIPE, /*---6---*/
}				t_type;

typedef enum	s_quoted
{
	start_simple_quoted,
				non_quoted,
				start_double_quoted,
				simple_quoted,
				double_quoted,
				end_simple_quoted,
				end_double_quoted,
}				t_quoted;

/*ESTA ES LA STRUCT PARA GUARDAR LOS TOKENS*/
typedef struct	s_token
{
	char		*data;
	t_type		type_tok;
	t_quoted	quot_state;
	struct 		s_token *next;
}				t_token;

/*STRUCT BASE, TIPICA STRUCT PARA PASAR VARIABLES GENERALES*/
typedef struct	s_base
{
	char	**envp;
	int		exit_status; //probable futuro manejo de exit
}			t_base;

/*----FUNCTIONS----*/

void	free2d(char **arr);
char	**envp_dup(char **ae);

/*Tokenizer & Parser*/
int		lexer(t_token **l_tokens, char *str, char **envp);
char	**ft_split(char const *s, char c);
char	*asignar_palabra(const char *s, int len);
void	print_list(t_token **l_tokens);
void	init_list_token(t_token **tokens, char *str, int count, char **envp);
int		ft_count_word(char const *s, char c);
int		contador_letras_comis(char const *s, char c);
int		getype(char *str, char **enp, int *flag_quot);
int		is_simple_quoted(char *str, int *flag_quot);
int		is_double_quoted(char *str, int *flag_quot);
int		is_pipe(char *str);

/**BUILTINS**/
void	ft_pwd();
int		ft_echo(char **args);

#endif
