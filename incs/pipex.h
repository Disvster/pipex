/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/14 20:38:31 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/incs/libft.h"
# include <stdio.h>

typedef struct s_cmd
{
	int		fd[2];
	int		pid;
	char	*path;
	char	**args;
}				t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**envp;
	char	**argv;
	int		argc;
	int		cmd_count;
	t_cmd	*cmds;
}				t_pipex;

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
void	parse_commands(t_pipex *pipex);
t_cmd	*get_command(char *cmd_str, char **envp);
char	*find_cmd_path(char *cmd, char **envp);
char	*pipex_strjoin(char *path, char *cmd);

#endif
