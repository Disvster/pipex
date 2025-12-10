/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:49:48 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/10 22:08:39 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	pipex->infile = open(av[1], O_RDONLY);
	pipex->infile = open(av[2], O);
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
	return (0);
}
