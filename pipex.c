/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:02:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/03/31 17:03:07 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_error(t_data *data)
{
	if (errno == ENOENT || errno == EACCES)
		perror("Error with opening file.");
	else if (condition)
	{
		/* code */
	}
	if (data->fd_in > 0)
		close(data->fd_in);
}
void	init_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->child1 = -1;
	data->child2 = -1;
	data->pipe_fd[2] = -1;
	data->path_dir = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	// int	pipe_fd[2];
	// pid_t	child1;
	// pid_t	child2;

	if (argc < 5)
	{
		ft_printf("Wrong number of arguments\n");
		return (0);
	}
	init_data(&data);
	data.pipes_count = argc - 4;
	if (check_input(&data, argc, argv, envp) == -1)

	// fd_in = open(argv[1], O_RDONLY);
	// if (fd_in == -1)
	// 	handle_error();

		// if (pipe(pipe_fd[2] == -1))
		// 	return (error());
		// child1 = fork();
}
