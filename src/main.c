/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:49:48 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/16 19:58:03 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex->infile = open(av[1], O_RDONLY);
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex->argc = ac;
	pipex->argv = av;
	pipex->envp = envp;
	pipex->cmd_count = ac - 3;
	pipex->cmds = ft_calloc(pipex->cmd_count, sizeof(t_cmd));
	// if (!pipex->cmds)// TODO:
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		write(2, "Wrong number of arguments; Usage is:\n", 37);
		write(2, "\n$>./pipex infile cmd1 cmd2 outfile\n\n", 37);
		return (1);
	}
	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipex(&pipex,  ac, av, envp);
	exec_pipe(&pipex);
	return (0);
}
