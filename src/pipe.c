/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:19:10 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/16 19:57:55 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	exec_pipe(t_pipex *pipex)
{// NOTE: hardcoded for 2 commands rn
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(pipex->fds);
	child1 = fork();
	if (child1 == -1)
		return (perror("Fork1: "));
	else if (child1 == 0)
		exec_cmd1(pipex);
	close(pipex->infile);
	close(pipex->fds[1]);
	child2 = fork();
	if (child2 == -1)
		return (perror("Fork2: "));
	else if (child2 == 0)
		exec_cmd2(pipex);
	close(pipex->outfile);
	close(pipex->fds[0]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
