/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:58:25 by arolland          #+#    #+#             */
/*   Updated: 2021/12/20 21:39:35 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	open_pipes(t_command *cmd, t_info *info)
{
	while (++cmd->pipes->o < info->nbr_pipe)
	{
		if (pipe(cmd->pipes->pipes[cmd->pipes->o]) == -1)
		{
			ft_putstr_fd("Error\nPipe creation failed\n", 2);
			free_all(cmd, info);
			exit(EXIT_FAILURE);
		}
	}
}

void	do_fork(t_command *cmd, t_info *info)
{
	cmd->pipes->pids[cmd->pipes->i] = fork();
	if (cmd->pipes->pids[cmd->pipes->i] == -1)
	{
		ft_putstr_fd("Error\nProcess creation failed\n", 2);
		free_all(cmd, info);
		exit(EXIT_FAILURE);
	}
}

void	free_cmd(t_command *cmd, char **args, t_info *info)
{
	if (args[0] == NULL)
	{
		if (args)
		{
			ft_putstr_fd("Command not found : «  »\n", 2);
			free_tab(args);
			args = NULL;
		}
		free_all(cmd, info);
		exit(EXIT_FAILURE);
	}
}

void	free_paths(t_command *cmd, char *paths, char **args, t_info *info)
{
	if (paths == NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_arr(&paths);
		free_tab(args);
		paths = NULL;
	}
	free_all(cmd, info);
	exit(EXIT_FAILURE);
}
