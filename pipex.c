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

	printf("i = %d\n", i);
	fflush(0);

	if (i == 0)
	{
		printf("aaa\n");
		if (open_file(data, argv[1], i) == -1)
			exit(1);
		//close(data->pipe_fd[2 * i]);
		printf("bbb\n");
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
		{
			perror("Failed to redirect stdin to input file");
			exit(1);
		}
		printf("%d = fd_in\n", data->fd_in);
		close(data->fd_in);
		printf("middle\n");
		printf("%d = pipe_fd0\n %d = pipe_fd1\n", data->pipe_fd[2 * i], data->pipe_fd[2 * i + 1]);
		fflush(0);
		printf("i = %d\n", i);
		if (dup2(data->pipe_fd[2 * i + 1], STDOUT_FILENO) == -1)
		{
			perror("Failed to redirect stdout to pipe");
			exit(1);
		}
		printf("ccc\n");
		close(data->pipe_fd[2 * i + 1]);
	}
	else if (i == data->command.cmd_count - 1)
	{
		if (open_file(data, argv[data->command.cmd_count + 2], i) == -1)
			exit(1);
		//close(data->pipe_fd[2 * i + 1]);
		dup2(data->pipe_fd[2 * i - 2], STDIN_FILENO);
		close(data->pipe_fd[2 * i - 2]);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	else
	{
		//close(data->pipe_fd[2 * i - 1]);
		dup2(data->pipe_fd[2 * i - 2], STDIN_FILENO);
		close(data->pipe_fd[2 * i - 2]);
		//close(data->pipe_fd[2 * i]);
		dup2(data->pipe_fd[2 * i + 1], STDOUT_FILENO);
		close(data->pipe_fd[2 * i + 1]);
	}
	printf("Command: %d - %s\n", i+2, argv[i+2]);
	fflush(0);
	if (check_command(data, argv[i + 2]) == -1)
		exit(1);

	printf("%s\n", data->command.cmd_path);
	fflush(0);
	// printf("%s\n", data->command.cmd_argv[1]);
	// fflush(0);

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
	while (i < data->command.cmd_count)
	{
		printf("%d - child_pid\n", data->child_pid[i]);
		if (waitpid(data->child_pid[i], NULL, 0) == -1)
		{
			perror("Error waiting for child process");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data->command.cmd_count - 1)
	{
		close(data->pipe_fd[2 * i]);
		close(data->pipe_fd[2 * i + 1]);
		i++;
	}
}

static void	create_pipe(t_data *data, int i)
{
	if (pipe(&data->pipe_fd[2 * i]) == -1)
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
	if (set_path(&data, envp) == -1)
		return (0);
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
		{
			child_process(&data, i, argv, envp);
		}
		// free(data.command.cmd_path);
		// free_array(data.command.cmd_argv);
		i++;
	}
	parent_process(&data);
	finish_program(&data);
}
