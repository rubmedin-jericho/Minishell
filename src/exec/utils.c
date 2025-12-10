#include "minishell.h"

void	fatal(const char *msg)
{
	perror(msg);
	exit(1);
}
