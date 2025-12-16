/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:40:19 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/16 19:53:49 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	exec_cmd1(t_pipex *pipex)
{
	parse_commands(pipex, 1);
	dup2(pipex->infile, 0);// TODO: handle errors on dup2 and execve
	dup2(pipex->fds[1], 1);
	close(pipex->infile);
	close(pipex->outfile);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	execve(pipex->cmds[0].path, pipex->cmds[0].args, pipex->envp);
}

void	exec_cmd2(t_pipex *pipex)
{
	parse_commands(pipex, 2);
	dup2(pipex->fds[0], 0);// TODO: handle errors on dup2 and execve
	dup2(pipex->outfile, 1);
	close(pipex->outfile);
	close(pipex->fds[0]);
	execve(pipex->cmds[1].path, pipex->cmds[1].args, pipex->envp);
}
