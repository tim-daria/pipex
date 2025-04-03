/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:02:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/04/02 17:52:08 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_data *data, int i, char *argv[], char *envp[])
{
	int	signal;

	if (i == 0)
	{
		if (open_file(data, argv[1], i) == -1)
			exit(1);
		close(data->pipe_fd[i][0]);
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
		dup2(data->pipe_fd[i][1], STDOUT_FILENO);
		close(data->pipe_fd[i][1]);
	}
	else if (i == data->command.cmd_count - 1)
	{
		if (open_file(data, argv[data->command.cmd_count + 2], i) == -1)
			exit(1);
		close(data->pipe_fd[i - 1][1]);
		dup2(data->pipe_fd[i - 1][0], STDIN_FILENO);
		close(data->pipe_fd[i - 1][0]);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	else
	{
		close(data->pipe_fd[i - 1][1]);
		dup2(data->pipe_fd[i - 1][0], STDIN_FILENO);
		close(data->pipe_fd[i - 1][0]);
		close(data->pipe_fd[i][0]);
		dup2(data->pipe_fd[i][1], STDOUT_FILENO);
		close(data->pipe_fd[i][1]);
	}
	if (check_command(data, argv[i + 2]) == -1)
		exit(1);
	signal = execve(data->command.cmd_path, data->command.cmd_argv, envp);
	if (signal == -1)
	{
		perror("Execution failed");
		exit(1);
	}
}

void	parent_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->command.cmd_count - 1)
	{
		close(data->pipe_fd[i][0]);
		close(data->pipe_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < data->command.cmd_count)
	{
		waitpid(data->child_pid[i], NULL, 0);
		i++;
	}
}

static void	create_pipe(t_data *data, int i)
{
	if (pipe(data->pipe_fd[i]) == -1)
	{
		perror("Pipe failed");
		handle_error(data);
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
	init_data(&data, argc);
	printf("a\n");
	fflush(0);
	if (set_path(&data, envp) == -1)
		return (0);
	printf("Am i here?\n");
	fflush(0);
	i = 0;
	while (i < data.command.cmd_count)
	{
		if (i < data.command.cmd_count - 1)
			create_pipe(&data, i);
		data.child_pid[i] = fork();
		if (data.child_pid[i] == -1)
		{
			perror("Fork failed");
			handle_error(&data);
			exit(1);
		}
		else if (data.child_pid[i] == 0)
			child_process(&data, i, argv, envp);
		free_array(data.command.cmd_argv);
		i++;
	}
	parent_process(&data);
	finish_program(&data);
}
