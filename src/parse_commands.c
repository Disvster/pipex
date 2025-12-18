/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:01:53 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/16 20:30:42 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

int	get_command(char *cmd_str, char **envp, t_cmd *cmd)
{
	int		wc;
	int		i;
	char	**split_cmd;

	wc = count_words(cmd_str, ' ');
	split_cmd = ft_split(cmd_str, ' ');
	if (!split_cmd)
		return (-1); // TODO:
	if (wc)
		cmd->path = find_cmd_path(split_cmd[0], envp);
	if (!cmd->path)
		// return (free(split_cmd), NULL);// TODO:
		return (-1);// TODO:
	i = -1;
	cmd->args = ft_calloc(wc + 1, sizeof(char *));
	// if (!info->args)
	// 	return (free(split_cmd, path),NULL)// TODO:
	while (++i < wc && split_cmd[i])
	{
		cmd->args[i] = ft_strdup(split_cmd[i]);
		// if (!info->args[i - 1])
		// 	return (free(split_cmd, info-args, info->path),NULL)// TODO:
	}
	cmd->args[i] = NULL;
	// return (free(split_cmd), info);// TODO:
	return (1);// TODO:
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*test;
	int		i;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp, ':');
	paths[0] = ft_strchr(paths[0], '/');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		if (ft_strchr(cmd, '/') != 0 && access(test, X_OK) == 0)// WARNING: this might not work
			break ;
		test = pipex_strjoin(paths[i], cmd);
		if (!test)
			return (/*free_paths(paths)*/NULL);// TODO:
		if (access(test, X_OK) == 0)
			break ;
		else if (paths[i + 1] == NULL)
			// return(free(everything), */exit(127));
			exit(127);// TODO:
		free(test);
	}
	//free_paths(paths)// TODO:
	return (test);
}

char	*pipex_strjoin(char *path, char *cmd)
{
	char	*new_cmd;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	new_cmd = ft_calloc(len, sizeof(char));
	if (!new_cmd)
		return (NULL);
	ft_strlcpy(new_cmd, path, ft_strlen(path) + 1);
	// new_cmd[ft_strlcpy(new_cmd, path, ft_strlen(path))] = '/';// WARNING: this might not work
	new_cmd[ft_strlen(new_cmd)] = '/';
	ft_strlcpy(new_cmd + ft_strlen(path) + 1, cmd, ft_strlen(cmd) + 1);
	ft_printf("new_cmd = %s\n", new_cmd);// HACK: db
	return (new_cmd);
}
