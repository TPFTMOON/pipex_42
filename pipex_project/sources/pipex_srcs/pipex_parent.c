/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:09:25 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/12 00:32:52 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe_if_needed(t_pipex *data, int *pipe_fds_stack)
{
	int	is_last_cmd;

	is_last_cmd = (data->cmd_index == data->num_cmds - 1);
	if (!is_last_cmd)
	{
		if (pipe(pipe_fds_stack) == -1)
			ft_exit_error(NULL, "pipe failed", data);
		data->pipe_fds = pipe_fds_stack;
	}
	else
	{
		data->pipe_fds = NULL;
		pipe_fds_stack[0] = -1;
		pipe_fds_stack[1] = -1;
	}
}

void	fork_and_run(t_pipex *data, int *pipe_fds_stack)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (data->pipe_fds)
			close_pipe_fds(data->pipe_fds);
		ft_exit_error(NULL, "fork failed", data);
	}
	if (pid == 0)
	{
		data->pipe_fds = pipe_fds_stack;
		run_child_process(data);
	}
	data->pids[data->cmd_index] = pid;
}

static void	ft_is_last_cmd_close(t_pipex *data, int is_last_cmd)
{
	if (!is_last_cmd)
	{
		if (data->pipe_fds[1] != -1)
			close(data->pipe_fds[1]);
		data->prev_pipe_read_end = data->pipe_fds[0];
	}
	else
	{
		if (data->prev_pipe_read_end != -1)
			close(data->prev_pipe_read_end);
		if (data->outfile_fd != -1)
		{
			close(data->outfile_fd);
			data->outfile_fd = -1;
		}
	}
}

void	handle_parent_process(t_pipex *data)
{
	int	is_last_cmd;

	if (data->prev_pipe_read_end != data->infile_fd)
	{
		if (data->prev_pipe_read_end != -1)
			close(data->prev_pipe_read_end);
	}
	if (data->cmd_index == 0 && data->infile_fd != -1)
	{
		close(data->infile_fd);
		data->infile_fd = -1;
	}
	is_last_cmd = (data->cmd_index == data->num_cmds - 1);
	ft_is_last_cmd_close(data, is_last_cmd);
}
