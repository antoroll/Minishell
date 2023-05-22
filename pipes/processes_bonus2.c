/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:25:55 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 22:19:20 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		if (g_exit_status == 1234567890)
			g_exit_status = 130;
	}
}

void	parent_bonus(t_command *cmd, t_info *info)
{
	int	i;
	int	k;

	i = -1;
	while (++i < info->nbr_pipe)
	{
		if (i != info->nbr_pipe)
			close(cmd->pipes->pipes[i][0]);
		if (i != 0)
			close(cmd->pipes->pipes[i][1]);
	}
	close(cmd->pipes->pipes[0][1]);
	close(cmd->pipes->pipes[info->nbr_pipe - 1][0]);
	k = -1;
	while (++k < info->nbr_pipe)
		waitpid(0, &cmd->pipes->status, WUNTRACED);
	if (WIFEXITED(cmd->pipes->status))
		g_exit_status = WEXITSTATUS(cmd->pipes->status);
	multipipes_signal_handling(cmd->pipes->status);
	unlink("heredoc");
}

void	close_pipes(t_command *cmd, t_info *info)
{
	while (++cmd->pipes->j < info->nbr_pipe)
	{
		if (cmd->pipes->i != cmd->pipes->j)
			if (close(cmd->pipes->pipes[cmd->pipes->j][0]) == -1)
				perror("Close failed");
		if (cmd->pipes->i + 1 != cmd->pipes->j)
			if (close(cmd->pipes->pipes[cmd->pipes->j][1]) == -1)
				perror("Close failed");
	}
}
