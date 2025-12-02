#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"

/* -------------------------------------------------- */
/* Helpers to create AST nodes manually for testing   */
/* -------------------------------------------------- */

t_ast *make_cmd(char **args)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = CMD;
    node->args = args;
    node->file = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_ast *make_pipe(t_ast *left, t_ast *right)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = PIPE;
    node->args = NULL;
    node->file = NULL;
    node->left = left;
    node->right = right;
    return node;
}

t_ast *make_redir(t_node_type type, t_ast *cmd, char *file)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = type;
    node->args = NULL;
    node->file = strdup(file);
    node->left = cmd;
    node->right = NULL;
    return node;
}

/* -------------------------------------------------- */
/* Dummy Shell struct                                 */
/* -------------------------------------------------- */

t_shell *make_shell(char **envp)
{
    t_shell *sh = malloc(sizeof(t_shell));
    sh->envp = envp;
    sh->ast = NULL;
    sh->exit_status = 0;
    return sh;
}

/* -------------------------------------------------- */
/* Exec node (this calls your exec_node implementation) */
/* -------------------------------------------------- */

extern void exec_node(t_ast *node, t_shell *sh);

/* -------------------------------------------------- */
/* Testing different examples                          */
/* -------------------------------------------------- */

void test_single_command(t_shell *sh)
{
    printf("=== TEST: simple command: ls -l ===\n");
    char *args[] = {"ls", "-l", NULL};
    sh->ast = make_cmd(args);
    exec_node(sh->ast, sh);
    free(sh->ast);
}

void test_pipe(t_shell *sh)
{
    printf("=== TEST: pipe: ls | wc -l | wc -l ===\n");

	char *ls_args[]  = {"ls", NULL};
    char *wc_args[]  = {"wc", "-l", NULL};
    char *wcc_args[] = {"wc", "-l", NULL};

    t_ast *ls  = make_cmd(ls_args);
    t_ast *wc  = make_cmd(wc_args);
    t_ast *wcc = make_cmd(wcc_args);

    // Build the pipeline recursively
    // (ls | wc) | wcc
    t_ast *first_pipe = make_pipe(ls, wc);
    t_ast *full_pipe  = make_pipe(first_pipe, wcc);

    sh->ast = full_pipe;

    // Execute the pipeline
    exec_node(sh->ast, sh);
}

void test_redir_out(t_shell *sh)
{
    printf("=== TEST: redirection: ls > out.txt ===\n");

    char *args[] = {"ls", NULL};
    t_ast *cmd = make_cmd(args);

    sh->ast = make_redir(REDIR_OUT, cmd, "out.txt");
    exec_node(sh->ast, sh);
}

void test_redir_in(t_shell *sh)
{
    printf("=== TEST: redirection: cat < infile ===\n");

    char *args[] = {"cat", NULL};
    t_ast *cmd = make_cmd(args);

    sh->ast = make_redir(REDIR_IN, cmd, "infile");
    exec_node(sh->ast, sh);
}

/* -------------------------------------------------- */
/* Main                                                */
/* -------------------------------------------------- */

int main(int argc, char **argv, char **envp)
{
    t_shell *sh = make_shell(envp);

    int choice = -1;
    
	printf("\nSelect test:\n");
	printf("1 = simple command\n");
	printf("2 = pipe\n");
	printf("3 = redir out\n");
	printf("4 = redir in\n");
	printf("0 = exit\n> ");

	if (scanf("%d", &choice) != 1)
	{
		printf("Invalid input. Exiting.\n");
		return (0);
	}
	
	else if (choice == 1)
		test_single_command(sh);
	else if (choice == 2)
		test_pipe(sh);
	else if (choice == 3)
		test_redir_out(sh);
	else if (choice == 4)
		test_redir_in(sh);
	else
		printf("Unknown option.\n");
	return 0;
}
