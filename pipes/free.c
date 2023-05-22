/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:57:58 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 17:16:01 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	free_arr(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_all(t_command *cmd, t_info *info)
{
	int	i;

	i = -1;
	if (cmd->pipes->args)
		free_tab(cmd->pipes->args);
	if (cmd->pipes->pids)
		free(cmd->pipes->pids);
	if (cmd->pipes->pipes)
	{
		while (++i < (info->nbr_pipe + 1))
			free(cmd->pipes->pipes[i]);
		free(cmd->pipes->pipes);
	}
}

void	free_builtin(t_info *info, t_pipes *pipes)
{
	int	i;

	if (info->nbr_pipe > 1)
	{
		i = -1;
		if (pipes->args)
			free_tab(pipes->args);
		if (pipes->pids)
			free(pipes->pids);
		if (pipes->pipes)
		{
			while (++i < (info->nbr_pipe + 1))
				free(pipes->pipes[i]);
			free(pipes->pipes);
		}
	}
}
