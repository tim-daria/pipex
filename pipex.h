/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:03:29 by dtimofee          #+#    #+#             */
/*   Updated: 2025/04/02 15:19:39 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	int		cmd_count;
	pid_t	child1;
	pid_t	child2;
	int		pipe_fd[2];
	char	**path_file;
}	t_data;

void	init_data(t_data *data);
void	handle_error(t_data *data);
void	free_array(char **str_array);

#endif
