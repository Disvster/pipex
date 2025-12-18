/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:23:51 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/18 12:24:11 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	error_exit(t_pipex *pipex, t_cmd *cmd, int exit_code)
{
	free
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (close(pipex->fds[0]) == -1)
		exit(exit_code);
	if (close(pipex->fds[1]) == -1)
		exit(exit_code);
	exit(exit_code);
}
