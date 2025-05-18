/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_and_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:57:32 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/14 15:50:48 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char *object, char *msg)
{
	int		len;
	char	*msg_with_colon;
	char	*full_msg;

	if (!object && !msg)
		return ;
	if (object == NULL)
	{
		len = ft_strlen(msg);
		write(STDERR_FD, msg, len);
	}
	else if (msg == NULL)
		perror(object);
	else
	{
		msg_with_colon = ft_strjoin(object, ": ");
		full_msg = ft_strjoin(msg_with_colon, msg);
		free(msg_with_colon);
		len = ft_strlen(full_msg);
		write(STDERR_FD, full_msg, len);
		free(full_msg);
	}
}

void	ft_exit_error(char *object, char *msg, t_pipex *data)
{
	ft_print_error(object, msg);
	cleanup_resources(data);
	exit(EXIT_FAILURE);
}

void	cleanup_resources(t_pipex *data)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	if (data->pids)
		free(data->pids);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
