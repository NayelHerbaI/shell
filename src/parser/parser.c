#include "minishell.h"

static t_ast    *parse_pipeline(t_lexbuf **tok)
{
    t_ast   *left;
    t_ast   *pipe_node;

    left = parse_command(tok);
    if (*tok && (*tok)->type == PIPE)
    {
        *tok = (*tok)->next;
        pipe_node = new_ast(AST_PIPE);
        pipe_node->left = left;
        pipe_node->right = parse_pipeline(tok);
        return (pipe_node);
    }
    return (left);
}

t_ast   *parser(t_lexbuf *tokens)
{
    return (parse_pipeline(&tokens));
}