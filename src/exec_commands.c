/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:40:19 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/18 13:40:20 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	exec_cmd1(t_pipex *pipex)
{
	t_cmd cmd;

	if (get_command(pipex->argv[2], pipex->envp, &cmd) == -1)
		exit(1);
	dup2(pipex->infile, 0);// TODO: handle errors on dup2 and execve
	dup2(pipex->fds[1], 1);
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	execve(cmd.path, cmd.args, pipex->envp);
}

void	exec_cmd2(t_pipex *pipex)
{
	t_cmd	cmd;

	if (get_command(pipex->argv[3], pipex->envp, &cmd) == -1)
		exit(1);
	dup2(pipex->fds[0], 0);// TODO: handle errors on dup2 and execve
	dup2(pipex->outfile, 1);
	close(pipex->outfile);
	close(pipex->fds[0]);
	execve(cmd.path, cmd.args, pipex->envp);
}
