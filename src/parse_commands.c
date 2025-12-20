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
		return (-1);
	if (wc)
		cmd->path = find_cmd_path(split_cmd[0], envp);
	if (!cmd->path)
		return (free_split(split_cmd), -1);
	cmd->args = ft_calloc(wc + 1, sizeof(char *));
	if (!cmd->args)
		return (free_split(split_cmd), free(cmd->path), -1);
	i = -1;
	while (++i < wc && split_cmd[i])
	{
		cmd->args[i] = ft_strdup(split_cmd[i]);
		if (!cmd->args[i])
		{
			while (i >= 0)
				free(cmd->args[i--]);
			free(cmd->args);
			free(cmd->path);
			return (free_split(split_cmd), free_split(cmd->args), -1);
		}
	}
	cmd->args[i] = NULL;
	free_split(split_cmd);
	return (1);
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
	if (!paths)
		return (NULL);
	if (ft_strncmp(paths[0], "PATH=", 5) == 0)
		ft_memmove(paths[0], paths[0] + 5, ft_strlen(paths[0] + 5) + 1);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (free_split(paths), ft_strdup(cmd));
		return (free_split(paths), NULL);
	}
	i = -1;
	while (paths[++i])
	{
		test = pipex_strjoin(paths[i], cmd);
		if (!test)
			return (free_split(paths), NULL);
		if (access(test, X_OK) == 0)
			break ;
		free(test);
		test = NULL;
	}
	return (free_split(paths), test);
}

char	*pipex_strjoin(char *path, char *cmd)
{
	char	*new_cmd;
	size_t	len;
	size_t	path_len;

	path_len = ft_strlen(path);
	len = path_len + ft_strlen(cmd) + 2;
	new_cmd = ft_calloc(len, sizeof(char));
	if (!new_cmd)
		return (NULL);
	ft_strlcpy(new_cmd, path, len);
	new_cmd[path_len] = '/';
	ft_strlcpy(new_cmd + path_len + 1, cmd, len - path_len - 1);
	return (new_cmd);
}
