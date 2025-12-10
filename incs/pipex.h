/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/10 21:31:04 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/incs/libft.h"
# include <stdio.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		cmd_count;
	char	**cmd_paths;
	char	**cmd_args;
}				t_pipex;

#endif
