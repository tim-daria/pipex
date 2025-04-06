/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:15:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/04/02 17:44:10 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	finish_program(t_data *data)
{
	free(data->pipe_fd);
	free(data->child_pid);
	free(data->command.cmd_path);
	// free_array(data->command.cmd_argv);
	free_array(data->path_file);
}

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
	if (errno == ENOENT || errno == EACCES)
		perror("Error with opening file.");
	if (data->fd_in > 0)
		close(data->fd_in);
	if (data->path_file[0] != NULL)
		free_array(data->path_file);
}

void	init_data(t_data *data, int argc)
{
	data->command.cmd_count = argc - 3;
	data->command.cmd_argv = NULL;
	data->command.cmd_path = NULL;
	data->fd_in = -1;
	data->fd_out = -1;
	data->path_file = NULL;
	data->child_pid = malloc(data->command.cmd_count * sizeof(pid_t));
	if (data->child_pid == NULL)
	{
		ft_printf("Malloc failed\n");
		exit(1);
	}
	data->pipe_fd = malloc((data->command.cmd_count - 1) * 2 * sizeof(int));
	if (data->pipe_fd == NULL)
	{
		ft_printf("Malloc failed\n");
		exit(1);
	}
}
