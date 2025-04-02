/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-01 13:15:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025-04-01 13:15:00 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free (str_array[i++]);
	free (str_array);
}

void	handle_error(t_data *data)
{
	//int	i;

	if (errno == ENOENT || errno == EACCES)
		perror("Error with opening file.");
	if (data->fd_in > 0)
		close(data->fd_in);
	// i = 0;
	// if (data->path_file[i] != NULL)
	// 	free_array(data->path_file);
}

void	init_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->child1 = -1;
	data->child2 = -1;
	data->pipe_fd[2] = -1;
	data->path_file = NULL;
}
