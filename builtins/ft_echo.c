#include "../minishell.h"
#include <stdio.h>

int	ft_echo(char *content, int n)
{
	if (content == NULL)
	{
		if (n == 1)
			return (0);
		printf("\n");
	}
	else
	{
		if (n == 1)
		{
			printf("%s", content);
			return (0);
		}
		printf("%s\n", content);
	}
	return (0);
}
/*
int main()
{
	ft_echo(NULL,1);
}*/