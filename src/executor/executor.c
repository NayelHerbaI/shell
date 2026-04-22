#include "minishell.h"

void    executor(t_ast *node, char **env)
{
    if (!node)
        return ;
    if (node->type == AST_PIPE)
        exec_pipe(node, env);
    else if (node->type == AST_CMD)
    {
        if (node->cmd && node->cmd->argv && node->cmd->argv[0])
        {
            if (is_builtin(node->cmd->argv[0]))
                exec_builtin(node, env);
            else
                exec_cmd(node, env);
        }
    }
}