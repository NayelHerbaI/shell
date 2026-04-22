#include "minishell.h"

void    exec_pipe(t_ast *node, char **env)
{
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (pipe(fd) < 0)
        return ;
    pid1 = fork();
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        executor(node->left, env);
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        executor(node->right, env);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}