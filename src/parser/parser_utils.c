#include "minishell.h"

t_ast   *new_ast(t_ast_type type)
{
    t_ast   *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    node->cmd = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_cmd   *new_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    return (cmd);
}

t_redir *new_redir(t_redir_type type, char *file)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file = ft_strdup(file);
    redir->next = NULL;
    return (redir);
}

void    free_redir(t_redir *redir)
{
    t_redir *next;

    while (redir)
    {
        next = redir->next;
        ft_free_str(redir->file);
        free(redir);
        redir = next;
    }
}

void    free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    free_ast(ast->left);
    free_ast(ast->right);
    if (ast->cmd)
    {
        ft_free_tab(ast->cmd->argv);
        free_redir(ast->cmd->redirs);
        free(ast->cmd);
    }
    free(ast);
}