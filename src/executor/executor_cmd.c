#include "minishell.h"

char    *find_path(char *cmd, char **env)
{
    char    **paths;
    char    *part;
    char    *full;
    int     i;

    if (ft_strchr(cmd, '/'))
        return (ft_strdup(cmd));
    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5))
        i++;
    if (!env[i])
        return (NULL);
    paths = ft_split(env[i] + 5, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        part = ft_strjoin(paths[i], "/");
        full = ft_strjoin(part, cmd);
        ft_free_str(part);
        if (access(full, X_OK) == 0)
        {
            ft_free_tab(paths);
            return (full);
        }
        ft_free_str(full);
        i++;
    }
    ft_free_tab(paths);
    return (NULL);
}

void    exec_cmd(t_ast *node, char **env)
{
    pid_t   pid;
    char    *path;
    int     status;

    pid = fork();
    if (pid < 0)
        return ;
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        exec_redirs(node->cmd->redirs);
        path = find_path(node->cmd->argv[0], env);
        if (!path)
        {
            ft_putstr_fd(node->cmd->argv[0], STDERR_FILENO);
            ft_putstr_fd(": command not found\n", STDERR_FILENO);
            exit(127);
        }
        execve(path, node->cmd->argv, env);
        ft_free_str(path);
        exit(1);
    }
    waitpid(pid, &status, 0);
}