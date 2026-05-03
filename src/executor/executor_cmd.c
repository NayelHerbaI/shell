/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:32:50 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/03 14:25:02 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_from_wait(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*part;
	char	*full;
	int		i;

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

int	exec_cmd(t_ast *node, t_input *input)
{
	pid_t	pid;
	char	*path;
	int		status;
	char	**env;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (exec_redirs(node->cmd->redirs))
			exit(1);
		env = env_to_array(input->env);
		if (!env)
			exit(1);
		path = find_path(node->cmd->argv[0], env);
		if (!path)
		{
			free_env_array(env);
			ft_putstr_fd(node->cmd->argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}
		execve(path, node->cmd->argv, env);
		ft_free_str(path);
		free_env_array(env);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (status_from_wait(status));
}
