/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:02:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/03/28 15:06:16 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	error(void)
{
	perror("Error");
	//return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_printf("Error! Wrong number of arguments\n");
		return (0);
	}

		int	fd_in;
		int	fd_out;
		int	pipe_fd[2];
		int	fd;
		pid_t	child1;
		pid_t	child2;

		fd_in = open(argv[1], O_RDONLY);
		if (fd == -1)
			handle_error();

			// after this line call dup function?
		if (pipe(pipe_fd[2] == -1))
			return (error());
		child1 = fork();
		if (child1 == -1)
			return (error()); //should I really end a programm?
		else if (child1 == 0)
		{

		}
		else if (child1 > 0)
		{

		}
}
