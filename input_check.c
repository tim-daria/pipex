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

static char	*find_path(t_data *data, char *cmd, char *envp[])
{
	char	*full_path;
	// char	**path_dir;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	full_path = ft_strtrim(envp[i], "PATH=");
	if (full_path == NULL || ft_strlen(full_path) == 0)
		{
			ft_printf("PATH is not set or empty\n");
			return (NULL);
		} // how to exit if full_path not found?
	data->path_dir = ft_split(full_path, ':');
	if (data->path_dir == NULL)
		ft_printf("Error with finding PATH\n");
	free(full_path);
}
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
			break;
		i++;
	}
	cmd = ft_substr(command, 0, i + 1);
	return (cmd);
}
static int	check_command(t_data *data, char *command, char *envp[])
{
	//char	*path;
	char	*cmd;

	cmd = extract_command(command);
	find_path(data, cmd, envp);
	// if (path == NULL)
	//check if command executable with access()
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
	if (check_inputfile(data, argv[1]) != -1)
		check_command(data, argv[2], envp);
}
