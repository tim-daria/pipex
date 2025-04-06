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

void	free_data(t_data *data)
{
	if (data->pipe_fd)
		free(data->pipe_fd);
	if (data->child_pid)
		free(data->child_pid);
	if (data->command.cmd_path)
		free(data->command.cmd_path);
	if (data->path_file[0])
		free_array(data->path_file);
}

void	close_fds(t_data *data, int i)
{
	if (i == 0)
	{
		close(data->pipe_fd[2 * i]);
		if (data->fd_in != -1)
			close(data->fd_in);
		close(data->pipe_fd[2 * i + 1]);
	}
	else if (i == data->command.cmd_count - 1)
	{
		close(data->pipe_fd[2 * i - 2]);
		close(data->pipe_fd[2 * i - 1]);
		if (data->fd_out != -1)
			close(data->fd_out);
	}
	else
	{
		close(data->pipe_fd[2 * i - 2]);
		close(data->pipe_fd[2 * i - 1]);
		close(data->pipe_fd[2 * i]);
		close(data->pipe_fd[2 * i + 1]);
	}
}

void	create_pipe(t_data *data, int i)
{
	if (pipe(&data->pipe_fd[2 * i]) == -1)
	{
		perror("Pipe failed");
		free_data(data);
		exit(1);
	}
}

void	free_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free (str_array[i++]);
	free (str_array);
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
		if (data->child_pid)
			free(data->child_pid);
		exit(1);
	}
}
