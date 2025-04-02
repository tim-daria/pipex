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
		return (0);

	// fd_in = open(argv[1], O_RDONLY);
	// if (fd_in == -1)
	// 	handle_error();

		// if (pipe(pipe_fd[2] == -1))
		// 	return (error());
		// child1 = fork();
}
