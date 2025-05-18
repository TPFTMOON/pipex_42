/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:08:57 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/12 10:26:35 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *data)
{
	data->infile_fd = open(data->argv[1], O_RDONLY);
	if (data->infile_fd == -1)
		ft_print_error(data->argv[1], NULL);
	data->outfile_fd = open(data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd == -1)
		ft_print_error(data->argv[data->argc - 1], NULL);
}
