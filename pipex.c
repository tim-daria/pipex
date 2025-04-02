/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:02:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/04/02 16:20:14 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
static void	create_pipe(t_data *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		i;

	if (argc < 5)
	{
		ft_printf("Wrong number of arguments\n");
		return (0);
	}
	init_data(&data);
	data.cmd_count = argc - 3;
	if (set_path(&data, envp) == -1) //do I need handle_error here?
		return (0);
	i = 0;
	while (i < data.cmd_count)
	{
		create_pipe(&data);
	}

}
