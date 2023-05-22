/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:55:53 by arolland          #+#    #+#             */
/*   Updated: 2021/12/22 22:05:37 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	ft_export(t_data *data, t_info *info, t_command *cmd, t_pipes *pipes)
{
	g_exit_status = 0;
	data->env_refresh = get_env(data->env);
	if (info->nbr_pipe > 1)
	{
		if ((ft_strcmp(cmd[pipes->i].args[0], "export") == 0)
			&& cmd[pipes->i].args[1] == NULL)
			display_export(data);
		data->env_doublon = check_doublon(data->env_refresh,
				cmd[pipes->i].args, data);
		if (data->env)
			free_tab(data->env);
		data->env = get_env_refresh_export(data->env_doublon,
				cmd[pipes->i].args, data);
		if (data->check == 0)
			free_tab(data->env_doublon);
		if (data->tab)
			free_tab(data->tab);
		free_export(data, cmd, info);
		exit(g_exit_status);
	}
	under_export(data, info, cmd);
	g_exit_status = 1;
	return (g_exit_status);
}

void	under_export(t_data *data, t_info *info, t_command *cmd)
{
	if (info->nbr_pipe == 1)
	{
		if ((ft_strcmp(cmd[0].args[0], "export") == 0)
			&& cmd[0].args[1] == NULL)
			display_export(data);
		if (cmd[0].args[1][0] != '\0')
		{
			data->check = -1;
			data->env_doublon = check_doublon(data->env_refresh,
					cmd[0].args, data);
			if (data->env)
				free_tab(data->env);
			data->env = get_env_refresh_export(data->env_doublon,
					cmd[0].args, data);
		}
		else
			error_export();
		free_cmd_export(data);
	}
}

void	free_export(t_data *data, t_command *cmd, t_info *info)
{
	free_tab(data->env_refresh);
	free(info->cmd);
	free_midway(cmd);
	free_all(cmd, info);
	free(cmd->builtin);
	rl_clear_history();
}

void	error_export(void)
{
	ft_putstr_fd("export: \'", 2);
	write(2, "", 0);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	free_cmd_export(t_data *data)
{
	free_tab(data->env_refresh);
	if (data->check == -1)
		free_tab(data->env_doublon);
}
