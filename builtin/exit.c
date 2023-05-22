/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:06:30 by arolland          #+#    #+#             */
/*   Updated: 2021/12/23 10:38:48 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	exit_prompt(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	int	exitt;

	exitt = 0;
	(void) data;
	(void) pipes;
	g_exit_status = 0;
	if (cmd[0].args[1])
		exitt = ft_atoi(cmd[0].args[1]);
	under_exit_prompt(info, cmd, data);
	udr_exit_bis(info, cmd, data, exitt);
	udr_exit_pipe(info, cmd, data, exitt);
	if (info->nbr_pipe > 1 && cmd[cmd->pipes->i].args[1]
		&& cmd[cmd->pipes->i].args[2])
	{
		g_exit_status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		free_midway(cmd);
		free(info->cmd);
		free(cmd->builtin);
		rl_clear_history();
		free_builtin(info, pipes);
		free_tab(data->env);
		exit(g_exit_status);
	}
	return (g_exit_status);
}

void	udr_exit_bis(t_info *info, t_command *cmd, t_data *data, int exitt)
{
	if (info->nbr_pipe > 1 && cmd[cmd->pipes->i].args[1]
		&& cmd[cmd->pipes->i].args[2] == NULL)
	{
		rl_clear_history();
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free(cmd->builtin);
		free_builtin(info, cmd->pipes);
		exit(exitt);
	}
}

void	udr_exit_pipe(t_info *info, t_command *cmd, t_data *data, int exitt)
{
	if (info->nbr_pipe > 1 && cmd[cmd->pipes->i].args[1] == NULL)
	{
		rl_clear_history();
		free(info->cmd);
		free_midway(cmd);
		free_tab(data->env);
		free(cmd->builtin);
		free_builtin(info, cmd->pipes);
		exit(exitt);
	}
}

void	under_exit_prompt(t_info *info, t_command *cmd, t_data *data)
{
	int	exitt;

	if (cmd[0].args[1])
		exitt = ft_atoi(cmd[0].args[1]);
	g_exit_status = 0;
	if (info->nbr_pipe == 1 && cmd[0].args[1] == NULL)
	{
		printf("exit\n");
		free(info->cmd);
		free_midway(cmd);
		free(cmd->builtin);
		rl_clear_history();
		free_tab(data->env);
		exit(g_exit_status);
	}
	udr_exit(info, cmd, data, exitt);
	if (info->nbr_pipe == 1 && cmd[0].args[1] && cmd[0].args[2])
	{
		g_exit_status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
}

void	udr_exit(t_info *info, t_command *cmd, t_data *data, int exitt)
{
	if (info->nbr_pipe == 1 && cmd[0].args[1] && cmd[0].args[2] == NULL)
	{
		printf("exit\n");
		free(info->cmd);
		free_midway(cmd);
		free(cmd->builtin);
		rl_clear_history();
		free_tab(data->env);
		exit(exitt);
	}
}
