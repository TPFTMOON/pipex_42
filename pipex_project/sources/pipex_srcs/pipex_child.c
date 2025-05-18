/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:10:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/12 10:30:13 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_input(t_pipex *data)
{
	if (data->cmd_index == 0 && data->prev_pipe_read_end == -1)
		ft_exit_error(NULL, NULL, data);
	if (dup2(data->prev_pipe_read_end, STDIN_FD) == -1)
		ft_exit_error(NULL, "dup2 stdin failed\n", data);
	if (data->prev_pipe_read_end != -1)
		close(data->prev_pipe_read_end);
}

static void	redirect_output(t_pipex *data)
{
	int	is_last_cmd;

	is_last_cmd = (data->cmd_index == data->num_cmds - 1);
	if (!is_last_cmd)
	{
		if (data->pipe_fds[0] != -1)
			close(data->pipe_fds[0]);
		if (dup2(data->pipe_fds[1], STDOUT_FD) == -1)
			ft_exit_error(NULL, "dup2 stdout pipe failed\n", data);
		if (data->pipe_fds[1] != -1)
			close(data->pipe_fds[1]);
	}
	else
	{
		if (dup2(data->outfile_fd, STDOUT_FD) == -1)
			ft_exit_error(NULL, "dup2 stdout file failed\n", data);
		if (data->outfile_fd != -1)
			close(data->outfile_fd);
	}
}

static void	ft_cmd_not_found_free(t_pipex *data, char *cmd_path,
		char **cmd_args)
{
	if (!cmd_path)
	{
		ft_print_error(cmd_args[0], "command not found\n");
		cleanup_resources(data);
		free_split(cmd_args);
		exit(CMD_N_FOUND);
	}
}

static void	execute_command(t_pipex *data)
{
	char	*cmd_str;
	char	**cmd_args;
	char	*cmd_path;

	cmd_str = data->argv[data->cmd_index + 2];
	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args)
		ft_exit_error(NULL, "ft_split failed\n", data);
	if (!cmd_args[0])
	{
		free_split(cmd_args);
		ft_exit_error(NULL, "permission denied\n", data);
	}
	cmd_path = find_command_path(cmd_args[0], data->envp);
	ft_cmd_not_found_free(data, cmd_path, cmd_args);
	execve(cmd_path, cmd_args, data->envp);
	perror(cmd_path);
	free(cmd_path);
	free_split(cmd_args);
	exit(EXIT_FAILURE);
}

void	run_child_process(t_pipex *data)
{
	if (data->cmd_index != data->num_cmds - 1 && data->outfile_fd != -1)
		close(data->outfile_fd);
	if (data->cmd_index != 0 && data->infile_fd != -1)
		close(data->infile_fd);
	redirect_input(data);
	redirect_output(data);
	execute_command(data);
}
