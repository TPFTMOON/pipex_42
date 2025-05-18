/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:56 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/14 15:55:55 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_data(t_pipex *data, int argc, char **argv, char **envp)
{
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->num_cmds = argc - 3;
	data->cmd_index = 0;
	data->pipe_fds = NULL;
	data->prev_pipe_read_end = -1;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->exit_status = 0;
	data->pids = malloc(sizeof(pid_t) * data->num_cmds);
	if (!data->pids)
		ft_exit_error(NULL, "malloc pids failed", data);
}

void	run_pipeline(t_pipex *data)
{
	int	pipe_fds_stack[2];

	pipe_fds_stack[0] = -1;
	pipe_fds_stack[1] = -1;
	data->pipe_fds = pipe_fds_stack;
	data->prev_pipe_read_end = data->infile_fd;
	while (data->cmd_index < data->num_cmds)
	{
		create_pipe_if_needed(data, pipe_fds_stack);
		fork_and_run(data, pipe_fds_stack);
		handle_parent_process(data);
		data->cmd_index++;
	}
}

void	wait_for_children(t_pipex *data)
{
	int	i;
	int	status;
	int	last_status_val;

	i = 0;
	last_status_val = 0;
	while (i < data->num_cmds)
	{
		if (waitpid(data->pids[i], &status, 0) == -1)
			perror("waitpid failed");
		if (i == data->num_cmds - 1)
			last_status_val = status;
		i++;
	}
	data->exit_status = last_status_val;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_print_error(NULL, "\033[0;31musage error.\033[0m\ncorrect pipex usage:\n"
			"./pipex \"infile\" \"cmd1\" \"cmd2\" ... \"cmdN\" \"outfile\"\n");
		exit(EXIT_FAILURE);
	}
	initialize_data(&data, argc, argv, envp);
	open_files(&data);
	run_pipeline(&data);
	wait_for_children(&data);
	cleanup_resources(&data);
	if (WIFEXITED(data.exit_status))
		return (WEXITSTATUS(data.exit_status));
	else if (WIFSIGNALED(data.exit_status))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
