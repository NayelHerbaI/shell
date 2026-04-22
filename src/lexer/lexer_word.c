#include "minishell.h"

int lex_word(char *line, int i, t_lexbuf **tokens)
{
    int     start;
    char    *word;

    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t'
        && line[i] != '|' && line[i] != '<' && line[i] != '>'
        && line[i] != '\'' && line[i] != '"')
        i++;
    word = ft_substr(line, start, i - start);
    add_token(tokens, word, WORD);
    ft_free_str(word);
    return (i);
}