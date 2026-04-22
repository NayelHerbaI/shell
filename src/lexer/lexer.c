#include "minishell.h"

t_lexbuf    *lexer(char *line)
{
    t_lexbuf    *tokens;
    int         i;

    tokens = NULL;
    i = 0;
    while (line[i])
    {
        if (line[i] == '\'')
            i = lex_squote(line, i, &tokens);
        else if (line[i] == '"')
            i = lex_dquote(line, i, &tokens);
        else if (line[i] == '|')
            i = lex_pipe(line, i, &tokens);
        else if (line[i] == '>' || line[i] == '<')
            i = lex_redir(line, i, &tokens);
        else if (line[i] == ' ' || line[i] == '\t')
            i++;
        else
            i = lex_word(line, i, &tokens);
    }
    return (tokens);
}