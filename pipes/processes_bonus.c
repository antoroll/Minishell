/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:01:45 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 15:55:37 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	exec_multipipes(t_info *info, t_data *d, t_builtin *b, t_command *cmd)
{
	exec_builtin(cmd, d, b, info);
	if (d->ret == -1 || (d->ret >= 0 && info->nbr_pipe > 1))
	{
		parsing_errors(d, cmd, info, b);
		init_vars_pipes(cmd, info);
		open_pipes(cmd, info);
		while (++cmd->pipes->i < info->nbr_pipe)
		{
			do_fork(cmd, info);
			if (cmd->pipes->pids[cmd->pipes->i] == 0)
			{
				d->ret = is_builtin(cmd[cmd->pipes->i].args[0], b);
				if (cmd->pipes->args && (d->ret < 0))
					free_tab(cmd->pipes->args);
				close_pipes(cmd, info);
				first_command(cmd, info);
				middle_command(cmd, info);
				last_command(cmd, info);
				under_exec(cmd, b, d, info);
			}
		}
		parent_bonus(cmd, info);
		free_all(cmd, info);
	}
}

void	under_exec(t_command *cmd, t_builtin *b, t_data *data, t_info *info)
{
	data->ret = is_builtin(cmd[cmd->pipes->i].args[0], b);
	if (data->ret >= 0)
	{
		b[data->ret].func(data, info, cmd, cmd->pipes);
	}
	else
	{
		data->ret = execve_child(cmd->pipes, data, cmd, info);
	}
}

void	exec_builtin(t_command *cmd, t_data *data, t_builtin *b, t_info *info)
{
	int	save_stdout;
	int	save_stdin;

	data->ret = is_builtin(cmd[0].args[0], b);
	if (data->ret >= 0 && info->nbr_pipe == 1)
	{
		save_stdout = dup(1);
		save_stdin = dup(0);
		under_exec_builtin(cmd);
		b[data->ret].func(data, info, cmd, cmd->pipes);
		if (cmd[0].redir_in > 1)
		{
			dup2(save_stdin, 0);
			close(save_stdin);
		}
		if (cmd[0].redir_out > 1)
		{
			dup2(save_stdout, 1);
			close(save_stdin);
		}
	}
}

void	under_exec_builtin(t_command *cmd)
{
	if (cmd[0].redir_in > 1)
	{
		dup2(cmd[0].redir_in, 0);
		close(cmd[0].redir_in);
	}
	if (cmd[0].redir_out > 1)
	{
		dup2(cmd[0].redir_out, 1);
		close(cmd[0].redir_out);
	}
}
