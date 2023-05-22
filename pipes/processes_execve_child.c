/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_execve_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:24:33 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 18:52:13 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	execve_child(t_pipes *pipes, t_data *data, t_command *cmd, t_info *info)
{
	pipes->paths = path(pipes, data->env, cmd[pipes->i].args);
	execve_double_dot(cmd, info, data);
	execve_dot(cmd, info, data);
	if (execve(pipes->paths, cmd[cmd->pipes->i].args, data->env) == -1)
	{
		g_exit_status = 127;
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free_all(cmd, info);
		free(cmd->builtin);
		rl_clear_history();
		exit(g_exit_status);
	}
	return (0);
}

void	execve_dot(t_command *cmd, t_info *info, t_data *data)
{
	if (cmd[cmd->pipes->i].args[0]
		&& ft_strcmp(cmd[cmd->pipes->i].args[0], ".") == 0)
	{
		ft_putstr_fd("bash: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		g_exit_status = 2;
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free_all(cmd, info);
		free(cmd->builtin);
		rl_clear_history();
		exit(g_exit_status);
	}
}

void	execve_double_dot(t_command *cmd, t_info *info, t_data *data)
{
	if (cmd[cmd->pipes->i].args[0]
		&& ft_strcmp(cmd[cmd->pipes->i].args[0], "..") == 0)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[cmd->pipes->i].args[0], 2);
		g_exit_status = 127;
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free_all(cmd, info);
		free(cmd->builtin);
		rl_clear_history();
		exit(g_exit_status);
	}
}

void	parsing_errors(t_data *data, t_command *cmd, t_info *info, t_builtin *b)
{
	int	i;

	i = -1;
	info->flag_quote = 0;
	info->i = 0;
	if (info->nbr_pipe == 1)
	{
		cmd->pipes->path_parsing = path_parsing(data->env,
				cmd[0].args, b, info);
		if (cmd->pipes->path_parsing)
			free(cmd->pipes->path_parsing);
	}
	else if (info->nbr_pipe > 1)
	{
		while (++i < info->nbr_pipe)
		{
			info->flag_quote = 0;
			info->i = 0;
			cmd->pipes->path_parsing = path_parsing(data->env,
					cmd[i].args, b, info);
			if (cmd->pipes->path_parsing)
				free(cmd->pipes->path_parsing);
		}
	}
}
