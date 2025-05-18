/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:19:13 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/12 04:22:33 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"

# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

# define CMD_N_FOUND 127

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		num_cmds;
	int		cmd_index;
	int		*pipe_fds;
	int		prev_pipe_read_end;
	int		argc;
	char	**envp;
	char	**argv;
	int		exit_status;
	pid_t	*pids;
}	t_pipex;

// pipex_bonus.c
void	pipex(int argc, char **argv, char **envp);
void	initialize_data(t_pipex *data, int argc, char **argv, char **envp);
void	run_pipeline(t_pipex *data);
void	wait_for_children(t_pipex *data);

// pipex_errors_and_free_bonus.c:
void	ft_print_error(char *object, char *msg);
void	ft_exit_error(char *object, char *msg, t_pipex *data);
void	cleanup_resources(t_pipex *data);
void	free_split(char **arr);

// pipex_utils_bonus.c
void	close_pipe_fds(int *fds);
char	*find_command_path(char *cmd, char **envp);

// pipex_files_bonus.c
void	open_files(t_pipex *data);

// pipex_parent_bonus.c
void	create_pipe_if_needed(t_pipex *data, int *pipe_fds_stack);
void	fork_and_run(t_pipex *data, int *pipe_fds_stack);
void	handle_parent_process(t_pipex *data);

// pipex_child_bonus.c
void	run_child_process(t_pipex *data);

#endif
