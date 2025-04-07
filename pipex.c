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

void	cleanup_and_exit(t_data *data, int i, int err)
{
	close_fds(data, i);
	free_data(data);
	exit(err);
}

static void	first_child(t_data *data, int i, char *argv[])
{
	if (open_file(data, argv[1], i) == -1
		|| check_command(data, argv[i + 2]) != 0)
		cleanup_and_exit(data, i, 1);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->pipe_fd[2 * i + 1], STDOUT_FILENO);
	close_fds(data, i);
}

static void	last_child(t_data *data, int i, char *argv[])
{
	int	error;

	if (open_file(data, argv[data->command.cmd_count + 2], i) == -1)
		cleanup_and_exit(data, i, 1);
	error = check_command(data, argv[i + 2]);
	if (error != 0)
		cleanup_and_exit(data, i, error);
	dup2(data->fd_out, STDOUT_FILENO);
	dup2(data->pipe_fd[2 * i - 2], STDIN_FILENO);
	close_fds(data, i);
}

static void	child_process(t_data *data, int i, char *argv[], char *envp[])
{
	int	signal;

	if (i == 0)
		first_child(data, i, argv);
	else if (i == data->command.cmd_count - 1)
		last_child(data, i, argv);
	else
	{
		if (check_command(data, argv[i + 2]) != 0)
			cleanup_and_exit(data, i, 1);
		dup2(data->pipe_fd[2 * i - 2], STDIN_FILENO);
		dup2(data->pipe_fd[2 * i + 1], STDOUT_FILENO);
		close_fds(data, i);
	}
	signal = execve(data->command.cmd_path, data->command.cmd_argv, envp);
	if (signal == -1)
	{
		perror("Execution failed");
		free_array(data->command.cmd_argv);
		free(data->command.cmd_path);
		exit(1);
	}
}

static void	parent_process(t_data *data, int i)
{
	int	status;
	int	w;
	int	exit_code;

	w = waitpid(data->child_pid[i], &status, 0);
	if (w == -1)
	{
		perror("waitpid");
		free_data(data);
		exit(1);
	}
	if (i < data->command.cmd_count - 1)
		close(data->pipe_fd[2 * i + 1]);
	if (i > 0 && i < data->command.cmd_count)
		close(data->pipe_fd[2 * i - 2]);
	if (WEXITSTATUS(status) != 0 && i == data->command.cmd_count - 1)
	{
		exit_code = WEXITSTATUS(status);
		free_data(data);
		exit(exit_code);
	}
}

static void	interprocess_communication(t_data *data, char *argv[], char *envp[])
{
	int	i;

	i = 0;
	while (i < data->command.cmd_count)
	{
		if (i < data->command.cmd_count - 1)
			create_pipe(data, i);
		data->child_pid[i] = fork();
		if (data->child_pid[i] == -1)
		{
			perror("Fork failed");
			free_data(data);
			exit(1);
		}
		else if (data->child_pid[i] == 0)
			child_process(data, i, argv, envp);
		else
			parent_process(data, i);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (0);
	}
	init_data(&data, argc);
	if (set_path(&data, envp) == -1)
	{
		free_data(&data);
		return (0);
	}
	interprocess_communication(&data, argv, envp);
	free_data(&data);
}
