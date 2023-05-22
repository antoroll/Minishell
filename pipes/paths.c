/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:59:00 by arolland          #+#    #+#             */
/*   Updated: 2021/12/21 22:05:56 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*have_path(t_pipes *pipes, char **paths, char *cmd)
{
	int		i;
	char	*final_path;
	char	*half_path;

	i = 0;
	(void) pipes;
	if (cmd == NULL || cmd[0] == '\0')
		return ("<< >>");
	if (paths != NULL)
	{
		while (paths[i])
		{
			half_path = ft_strjoin(paths[i], "/");
			final_path = ft_strjoin(half_path, cmd);
			free_arr(&half_path);
			if (access(final_path, F_OK) == 0)
				return (final_path);
			free_arr(&final_path);
			i++;
		}
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (cmd);
}

char	**split_path(char *path, char **envp)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], path, ft_strlen(path)) == 0)
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	return (paths);
}

char	*path(t_pipes *pipes, char **envp, char **cmd)
{
	char	**paths;
	char	*path;

	paths = split_path("PATH=", envp);
	path = have_path(pipes, paths, *cmd);
	if (paths)
		free_tab(paths);
	return (path);
}
