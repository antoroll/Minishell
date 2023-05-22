/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:00:15 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:31:42 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

char	*have_path_parsing(char **paths, char *cmd, t_builtin *b, t_info *info)
{
	if (cmd == NULL)
		return (NULL);
	check_quotes(cmd, info);
	if (paths != NULL)
	{
		while (paths[info->i] && info->flag_quote != 1)
		{
			info->half_path = ft_strjoin(paths[info->i], "/");
			info->final_path = ft_strjoin(info->half_path, cmd);
			free_arr(&info->half_path);
			if (access(info->final_path, F_OK) == 0)
				return (info->final_path);
			free_arr(&info->final_path);
			info->i++;
		}
	}
	else
		check_cmd(cmd);
	if (access(cmd, F_OK) == 0)
	{
		info->cmd_bis = ft_strdup(cmd);
		return (info->cmd_bis);
	}
	check_builtin(info, cmd, b, paths);
	return (NULL);
}

char	**split_path_parsing(char *path, char **envp)
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

char	*path_parsing(char **envp, char **cmd, t_builtin *builtin, t_info *info)
{
	char	**paths;
	char	*path;

	paths = split_path_parsing("PATH=", envp);
	path = have_path_parsing(paths, *cmd, builtin, info);
	if (paths)
		free_tab(paths);
	return (path);
}
