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

static void	spawn_child2(t_pipex *pipex, pid_t *child2)
{
	*child2 = fork();
	if (*child2 == -1)
		return (perror("Fork: "));
	else if (*child2 == 0)
		exec_cmd2(pipex);
}

static void	spawn_child1(t_pipex *pipex, pid_t *child1)
{
	*child1 = fork();
	if (*child1 == -1)
		return (perror("Fork: "));
	else if (*child1 == 0)
		exec_cmd1(pipex);
}

static void	wait_children_and_exit(pid_t child1, pid_t child2)
{
	int	status;

	if (waitpid(child1, &status, 0) == -1)
		perror("waitpid");
	if (waitpid(child2, &status, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else
		exit(EXIT_FAILURE);
}

void	exec_pipe(t_pipex *pipex)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->fds))
		return (perror("pipe: "));
	spawn_child1(pipex, &child1);
	close(pipex->infile);
	close(pipex->fds[1]);
	spawn_child2(pipex, &child2);
	close(pipex->outfile);
	close(pipex->fds[0]);
	wait_children_and_exit(child1, child2);
}
