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
		return (free_split(split_cmd), -1);// WARNING: might need ** @free_split
	i = -1;
	cmd->args = ft_calloc(wc + 1, sizeof(char *));
	if (!cmd->args)
		return (free_split(split_cmd), free(cmd->path), -1);
	while (++i < wc && split_cmd[i])
	{
		cmd->args[i] = ft_strdup(split_cmd[i]);
		if (!cmd->args[i - 1])
			return (free_split(split_cmd), free_split(cmd->args), -1);
	}
	cmd->args[i] = NULL;
	return (free_split(split_cmd), 1);
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
	if (ft_strncmp(paths[0], "PATH=", 5) == 0)
		ft_memmove(paths[0], paths[0] + 5, ft_strlen(paths[0] + 5) + 1);
	// paths[0] = ft_strchr(paths[0], '/');
	if (!paths)
		return (NULL);
	i = -1;
	// ft_printf("paths[0] = %s\n", paths[0]);// HACK: db
	while (paths[++i])
	{
		if (ft_strchr(cmd, '/') != 0 && access(test, X_OK) == 0)//WARNING:
			break ;
		test = pipex_strjoin(paths[i], cmd);
		if (!test)
			return (free_split(paths), NULL);
		if (access(test, X_OK) == 0)
			break ;
		else if (paths[i + 1] == NULL)
			return(free_split(paths), free(test), NULL);
			// exit(127);
		free(test);
	}
	return (free_split(paths), test);
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
	new_cmd[ft_strlen(new_cmd)] = '/';
	ft_strlcpy(new_cmd + ft_strlen(path) + 1, cmd, ft_strlen(cmd) + 1);
	// ft_printf("new_cmd = %s\n", new_cmd);// HACK: db
	return (new_cmd);
}
