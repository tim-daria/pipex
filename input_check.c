/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:56:27 by dtimofee          #+#    #+#             */
/*   Updated: 2025/03/31 17:07:07 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*extract_command(char *command)
{
	char	*cmd;
	int		i;
	size_t	len;

	len = ft_strlen(command) + 1;
	if (len - 1 == 0)
		return (-1);
	i = 0;
	while (len-- > 0)
	{
		if (command[i] == ' ' || command[i] == '\0')
			break ;
		i++;
	}
	cmd = ft_substr(command, 0, i + 1);
	return (cmd);
}

static int	check_command(t_data *data, char *command, char *envp[])
{
	char	*cmd;
	char	*pathname;

	cmd = extract_command(command);
	if (find_path(data, cmd) == -1)
		return (-1);
	free(cmd);
	return (0);
}

static int	check_inputfile(t_data *data, char *file_in)
{
	data->fd_in = open(file_in, O_RDONLY);
	if (data->fd_in == -1)
	{
		handle_error(data);
		return (-1);
	}
	return (0);
}

int	check_input(t_data *data, int argc, char *argv[], char *envp[])
{
	if (set_path(data, envp) == -1)
	{
		handle_error(data);
		return (-1);
	}
	if (check_inputfile(data, argv[1]) != -1)
	{
		if (check_command(data, argv[2], envp) == -1)
			return (-1);
	}
	//check all other commands
}
