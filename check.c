/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:56:27 by dtimofee          #+#    #+#             */
/*   Updated: 2025/04/02 15:21:25 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*extract_command(t_data *data, char *command)
{
	data->command.cmd_argv = ft_split(command, ' ');
	if (data->command.cmd_argv == NULL)
	{
		ft_printf("Command not found\n");
		return (NULL);
	}
	return (data->command.cmd_argv[0]);
}


static int	find_path(t_data *data, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->path_file[i])
	{
		temp = ft_strjoin(data->path_file[i], cmd);
		if (temp == NULL)
		{
			ft_printf("Command not found\n");
			return (-1);
		}
		if (access(temp, X_OK) == 0)
		{
			data->command.cmd_path = temp;
			// free(temp);
			printf("%s - data_cmd_path\n", data->command.cmd_path);
			fflush(0);
			return (0);
		}
		free(temp);
		i++;
	}
	ft_printf("Command not found\n");
	return (-1);
}

int	check_command(t_data *data, char *command)
{
	char	*cmd;

	printf("I am in check_command\n");
	fflush(0);
	cmd = extract_command(data, command);
	printf("%s\n", cmd);
	fflush(0);
	if (cmd == NULL || find_path(data, cmd) == -1)
		return (-1);
	return (0);
}

int	open_file(t_data *data, char *file, int i)
{
	if (i == 0)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
		{
			perror("Error with opening file.");
			return (-1);
		}
	}
	else if (i == data->command.cmd_count - 1)
	{
		data->fd_out = open(file, O_CREAT | O_WRONLY);
		if (data->fd_out == -1)
		{
			perror("Error with opening file.");
			return (-1);
		}
	}
	return (0);
}
