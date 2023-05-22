/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:40 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 14:26:14 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	init_counters(t_command *cmd)
{
	cmd->pipes->i = -1;
	cmd->pipes->j = -1;
	cmd->pipes->k = -1;
	cmd->pipes->o = -1;
	cmd->pipes->g = -1;
	cmd->pipes->flag2 = 0;
	cmd->pipes->flag3 = 0;
	cmd->pipes->pid = 0;
	cmd->pipes->paths = NULL;
	cmd->pipes->args = NULL;
	cmd->pipes->pipes = NULL;
	cmd->pipes->pids = NULL;
	cmd->pipes->arr = NULL;
	cmd->pipes->in = 0;
	cmd->pipes->out = 0;
	cmd->pipes->flag_pipe = 0;
	cmd->pipes->heredoc_flag = 0;
	cmd->pipes->limiter = 0;
	cmd->pipes->heredoc = NULL;
	cmd->pipes->flag = 0;
}

void	init_vars_pipes(t_command *cmd, t_info *info)
{
	init_counters(cmd);
	cmd->pipes->pids = malloc(sizeof(int) * (info->nbr_pipe + 1));
	if (!cmd->pipes->pids)
		free_all(cmd, info);
	cmd->pipes->pipes = malloc(sizeof(int *) * (info->nbr_pipe + 1));
	if (!cmd->pipes->pipes)
		free(cmd->pipes->pipes);
	while (++cmd->pipes->g < (info->nbr_pipe + 1))
	{
		cmd->pipes->pipes[cmd->pipes->g] = malloc(2 * sizeof(int));
		if (!cmd->pipes->pipes[cmd->pipes->g])
			free_all(cmd, info);
	}
}
