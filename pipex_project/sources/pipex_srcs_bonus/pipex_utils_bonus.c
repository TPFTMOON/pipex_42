/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:08:31 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/12 10:32:13 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipe_fds(int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

static char	*check_path(char *path, char *cmd)
{
	char	*slash_cmd;
	char	*full_path;

	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	full_path = ft_strjoin(path, slash_cmd);
	free(slash_cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_path_env(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*executable_path;
	int		i;

	path_var = NULL;
	i = 0;
	while (envp && envp[i] && !path_var)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_var = envp[i] + 5;
		i++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	executable_path = NULL;
	while (paths[i] && !executable_path)
		executable_path = check_path(paths[i++], cmd);
	free_split(paths);
	return (executable_path);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			path = ft_strdup(cmd);
			if (!path)
				return (NULL);
			return (path);
		}
		else
			return (NULL);
	}
	else
	{
		path = search_path_env(cmd, envp);
		return (path);
	}
}
