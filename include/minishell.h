#ifndef MINISHELL_H
# define MINISHELL_H

/*----LIBRERY----*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

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
				T_FLOW_OPERATOR, /*---7---*/
}				t_type;

typedef struct	s_flags
{
	int			flag_simple_quot;
	int			flag_double_quot;
}				t_flags;

/*ESTA ES LA STRUCT PARA GUARDAR LOS TOKENS*/
typedef struct	s_token
{
	char		*data;
	t_type		type_tok;
	struct 		s_token *next;
}				t_token;

/*STRUCT BASE, TIPICA STRUCT PARA PASAR VARIABLES GENERALES*/
typedef struct	s_base
{
	char	**envp;
	char	**commands;
	int		exit_status; //probable futuro manejo de exit
}			t_base;

/*----FUNCTIONS----*/

void	free2d(char **arr);
char	**envp_dup(char **ae);
void	clear_and_leave(t_base *base, char **args);

/*Tokenizer & Parser*/
int		lexer(t_token **l_tokens, char *str, char **envp, t_flags *flags);
char	**ft_split(char const *s, char c);
char	*asignar_palabra(const char *s, int len);
void	print_list(t_token **l_tokens);
void	init_list(t_token **tokens, char *str, char **envp, t_flags *flags);
int		ft_count_word(char const *s, char c);
int		contador_letras_comis(char const *s, char c);
int		getype(char *str, char **enp, t_flags *flags);
int		is_simple_quoted(char *str, t_flags *flags);
int		is_double_quoted(char *str, t_flags *flags);
int		is_pipe(char *str, t_flags *flags);
int		is_or_operator(char *str, t_flags *flags);
void	init_flags(t_flags *flags);
void	init_base(char **ae,t_base *base, t_token *tokens);

/**BUILTINS**/
int		ft_pwd();
int		ft_echo(char **args);
int		ft_env(t_base *base);
void	ft_exit(t_base *base, char **args, int is_child);

#endif
